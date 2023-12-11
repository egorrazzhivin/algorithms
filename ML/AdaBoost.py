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



class MyAdaBoostClassifier:
    """
    Multiclass AdaBoost implementation with SAMME.R algorithm
    """
    big_number = 1 << 32
    eps = 1e-8

    def __init__(
            self,
            n_estimators: int,
            base_estimator: tp.Type[sklearn.base.BaseEstimator],
            seed: int,
            **kwargs
    ):
        """
        :param n_estimators: count of estimators
        :param base_estimator: base estimator (practically tree classifier)
        :param seed: global seed
        :param kwargs: keyword arguments of base estimator
        """
        self.seed = seed
        self.eps = 1e-8
        self.n_classes = None
        self.error_history = []  # this is to track model learning process
        self.n_estimators = n_estimators
        self.rng = np.random.default_rng(seed)
        self.base_estimator = base_estimator
        self.base_estimator_kwargs = kwargs
        # deduce which keywords are used to set seed for an estimator (sklearn or own tree implementation)
        signature = inspect.signature(self.base_estimator.__init__)
        self.seed_keyword = None
        if 'seed' in signature.parameters:
            self.seed_keyword = 'seed'
        elif 'random_state' in signature.parameters:
            self.seed_keyword = 'random_state'
        self.estimators = []

    def create_new_estimator(
            self,
            seed: int
    ):
        """
        create new base estimator with proper keywords
        and new *unique* seed
        :param seed:
        :return:
        """
        if self.seed_keyword is not None:
            self.base_estimator_kwargs[self.seed_keyword] = seed
        return self.base_estimator(**self.base_estimator_kwargs)
        

    def get_new_weights(
            self,
            true_labels: np.ndarray,
            predictions: np.ndarray,
            weights: np.ndarray
    ):
        """
        Calculate new weights according to SAMME.R scheme
        :param true_labels: [n_classes]
        :param predictions: [n_samples, n_classes]
        :param weights:     [n_samples]
        :return: normalized weights for next estimator fitting
        """
        n_samples = predictions.shape[0]
        n_classes = predictions.shape[1]
        new_weights = weights
        y = np.full((n_samples, n_classes), -1/(n_classes - 1))
        y[np.arange(n_samples), true_labels] = 1
        alpha = -(n_classes - 1)/(n_classes)
        new_weights = weights * np.exp(alpha * np.sum(y * np.log(predictions + self.eps), axis = 1)) 
        return new_weights / np.sum(new_weights)

    @staticmethod
    def get_estimator_error(
            estimator: sklearn.base.BaseEstimator,
            X: np.ndarray,
            y: np.ndarray,
            weights: np.ndarray
    ):
        """
        calculate weighted error of an estimator
        :param estimator:
        :param X:       [n_samples, n_features]
        :param y:       [n_samples]
        :param weights: [n_samples]
        :return:
        """
        y_pred = estimator.predict(X)
        error = np.sum(weights * (y_pred != y))
        return error / np.sum(weights)

    def fit(
            self,
            X: np.ndarray,
            y: np.ndarray
    ):
        """
        sequentially fit estimators with updated weights on each iteration
        :param X: [n_samples, n_features]
        :param y: [n_samples]
        :return: self
        """
        self.error_history = []
        # compute number of classes for internal use
        self.n_classes = np.unique(y).shape[0]
        # init weights uniformly over all samples
        weights = np.ones(X.shape[0])/X.shape[0]
        # sequentially fit each model and adjust weights
        for seed in self.rng.choice(
                max(MyAdaBoostClassifier.big_number, self.n_estimators),
                size=self.n_estimators,
                replace=False
        ):
            # add newly created estimator
            self.estimators.append(self.create_new_estimator(seed))
            # fit added estimator to data with current sample weights
            current = self.estimators[-1]
            current.fit(X, y)
            # compute probability predictions
            probs = current.predict_proba(X)
            # calculate weighted error of last estimator and append to error history
            self.error_history.append(self.get_estimator_error(current, X, y, weights))
            # compute new adjusted weights
            weights = self.get_new_weights(y, probs, weights)

        return self

    def predict_proba(
            self,
            X: np.ndarray
    ):
        """
        predicts probability of each class
        :param X: [n_samples, n_features]
        :return: array of probabilities of a shape [n_samples, n_classes]
        """
        # calculate probabilities from each estimator and average them, clip logarithms using self.eps
        # use softmax to ensure probabilities sum to 1, use numerically stable implementation
        n_samples = X.shape[0]
        n_classes = X.shape[1]
        probabilities = np.full((n_samples, n_classes), 0)
        for x in self.estimators:
            probabilities += x.predict_proba(X)
        return probabilities / len(self.estimators)

    def predict(
            self,
            X: np.ndarray
    ):
        """
        predicts class (use predicted class probabilities)
        :param X: [n_samples, n_features]
        :return: array class predictions of a shape [n_samples]
        """
        return np.array([self.predict_proba(x) for x in X])
