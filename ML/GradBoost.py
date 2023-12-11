import contextlib
import inspect
import json
import os
import pathlib
import typing as tp
import uuid

import numpy as np
import pandas as pd
import sklearn
from sklearn.metrics._scorer import _check_multimetric_scoring
from sklearn.model_selection._validation import _score
from sklearn.tree import DecisionTreeRegressor
from sklearn.tree import DecisionTreeClassifier
from scipy.special import logsumexp    
    
class MyBinaryTreeGradientBoostingClassifier:
    """
    *Binary* gradient boosting with trees using
    negative log-likelihood loss with constant learning rate.
    Trees are to predict logits.
    """
    big_number = 1 << 32
    eps = 1e-8

    def __init__(
            self,
            n_estimators: int,
            learning_rate: float,
            seed: int,
            **kwargs
    ):
        """
        :param n_estimators: estimators count
        :param learning_rate: hard learning rate
        :param seed: global seed
        :param kwargs: kwargs of base estimator which is sklearn TreeRegressor
        """
        self.eps = 1e-8
        self.n_estimators = n_estimators
        self.learning_rate = learning_rate
        self.initial_logits = None
        self.rng = np.random.default_rng(seed)
        self.base_estimator = DecisionTreeRegressor
        self.base_estimator_kwargs = kwargs
        self.estimators = []
        self.loss_history = []  # this is to track model learning process

    def create_new_estimator(self, seed):
        #if self.seed_keyword is not None:
        #    self.base_estimator_kwargs[self.seed_keyword] = seed
        return self.base_estimator(**self.base_estimator_kwargs)

    @staticmethod
    def cross_entropy_loss(
            true_labels: np.ndarray,
            logits: np.ndarray
    ):
        """
        compute negative log-likelihood for logits,
        use clipping for logarithms with self.eps
        or use numerically stable special functions.
        This is used to track model learning process
        :param true_labels: [n_samples]
        :param logits: [n_samples]
        :return:
        """
        eps = 1e-10
        probabilities = 1 / (1 + np.exp(-logits))
        probabilities = np.clip(probabilities, eps, 1 - eps)
        loss = np.sum(true_labels * np.log(probabilities)) + np.sum((1 - true_labels) * np.log(1 - probabilities))

        return -loss


    @staticmethod
    def cross_entropy_loss_gradient(
            true_labels: np.ndarray,
            logits: np.ndarray
    ):
        """
        compute gradient of log-likelihood w.r.t logits,
        use clipping for logarithms with self.eps
        or use numerically stable special functions
        :param true_labels: [n_samples]
        :param logits: [n_samples]
        :return:
        """
        probas = 1 / (1 + np.exp(-logits))
        gradient = true_labels - probas
        return -gradient


    def fit(
            self,
            X: np.ndarray,
            y: np.ndarray
    ):
        """
        sequentially fit estimators to reduce residual on each iteration
        :param X: [n_samples, n_features]
        :param y: [n_samples]
        :return: self
        """
        self.loss_history = []
        eps = 1e-8
        # only should be fitted on datasets with binary target
        assert (np.unique(y) == np.arange(2)).all()
        # init predictions with mean target (mind that these are logits!)
        self.initial_logits = np.log((np.mean(y) + eps) / (1 - np.mean(y) + eps))
        # create starting logits
        logits = self.initial_logits
        # init loss history with starting negative log-likelihood
        self.loss_history.append(self.cross_entropy_loss(y, logits))
        # sequentially fit estimators with random seeds
        for seed in self.rng.choice(
                max(self.big_number, self.n_estimators),
                size=self.n_estimators,
                replace=False
        ):
            # add newly created estimator
            self.estimators.append(self.create_new_estimator(seed))
            # compute gradient
            gradient = self.cross_entropy_loss_gradient(y, logits)
            # fit estimator on gradient residual
            self.estimators[-1].fit(X, gradient)
            # adjust logits with learning rate
            logits -= self.learning_rate * self.estimators[-1].predict(X)
            # append new loss to history
            self.loss_history.append(self.cross_entropy_loss(y, logits))
        return self

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))
    
    def predict_proba(
            self,
            X: np.ndarray
    ):
        """
        :param X: [n_samples]
        :return:
        """
        # init logits using precalculated values
        #logits = self.initial_logits
        # sequentially adjust logits with learning rate
        #for estimator in self.estimators:
         #   logits -= self.learning_rate * estimator.predict(X)
        # don't forget to convert logits to probabilities
        #probas = self.sigmoid(logits)
        #return probas
        logits = self.initial_logits
        for estimator in self.estimators:
            logits -= self.learning_rate * estimator.predict(X)
        probas = np.exp(logits) / np.sum(np.exp(logits))
        return probas


    def predict(
            self,
            X: np.ndarray
    ):
        """
        calculate predictions using predict_proba
        :param X: [n_samples]
        :return:
        """
        probs = self.predict_proba(X)
        predictions = np.argmax(probs)
        return predictions
