import numpy as np
import pandas as pd
from scipy.special import expit

class LogisticRegression():
    '''
    SGDLogisticRegression
    
    parameters:
    alpha: regularization parameter
    lr: learning rate
    max_iter: maximum number of iterations
    threshold: threshold for probabilities
    batch_size: batch size of every step
    fit_intercept: add intercept or not
    '''

    def __init__(self, alpha=0, lr=0.5, max_iter=100000,
                 batch_size = 8, threshold = 0.5, 
                 fit_intercept=True):
        self.alpha = alpha
        self.lr = lr
        self.max_iter = max_iter
        self.fit_intercept = fit_intercept
        self.batch_size = batch_size
        self.threshold = threshold

    @staticmethod
    def _sigmoid(x):
        return expit(x)

    def _add_intercept(self, X) -> pd.DataFrame:
        #X: feature matrix
        #return: X with intercept

        X_copy = np.full((X.shape[0], X.shape[1] + 1), fill_value=1.)
        X_copy[:, :-1] = X

        return X_copy

    def fit(self, X, Y) -> np.array:
        #X: feature matrix
        #Y: true values

        assert X.shape[0] == Y.shape[0]

        if self.fit_intercept:  
            X_copy = self._add_intercept(X)
        else:
            X_copy = X.copy()

        self.coef_ = np.full((X_copy.shape[1]), fill_value = 1.)
        
        for i in range(self.max_iter):
            #theta_{t+1} = theta_{t} + lambda * (n / batch_size) * X_batch.T * (Y_batch - S_batch(theta_{t}))
            #where S_batch_{i} = expit(theta_{t}.T * X_batch_{i})
            indexes = np.random.choice(np.arange(X.shape[0]))
            X_batch = X_copy[indexes]
            Y_batch = Y[indexes]
            S_batch = _sigmoid(X_batch.dot(self.coef_))
            grad = -self.lr * (X_copy.shape[0] / self.batch_size) * X_batch.T.dot(Y_batch - S_batch) + 2 * self.alpha * self.coef_
            self.coef_ -= grad
                               
        return self.coef_

    def predict(self, X) -> np.array:
        #return: class of every object

        if self.fit_intercept:
            X_copy = self._add_intercept(X)
        else:
            X_copy = X.copy()

        assert X_copy.shape[1] == self.coef_.shape[0]

        predictions = _sigmoid(X_copy.dot(self.coef_))
        predictions[predictions <= self.threshold] = 0
        predictions[predictions > self.threshold] = 1

        return predictions

    def predict_proba(self, X) -> pd.DataFrame:
        #return: DataFrame with probabilities of 0 and 1

        if self.fit_intercept:
            X_copy = self._add_intercept(X)
        else:
            X_copy = X.copy()

        assert X_copy.shape[1] == self.coef_.shape[0]

        predictions = _sigmoid(X_copy.dot(self.coef_))
        predictions = pd.DataFrame(predictions, columns = ['1'])
        predictions['0'] = 1 - predictions['1']

        return prob_predictions
