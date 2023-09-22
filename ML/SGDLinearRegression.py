from sklearn.base import RegressorMixin
import numpy as np
import pandas as pd

class SGDLinearRegressor(RegressorMixin):
    def __init__(
        self,
        lr=0.01,
        regularization=1,
        delta_converged=0.01,
        max_steps=1000,
        batch_size=64,
    ) -> None:
        
        self.lr = lr
        self.regularization = regularization
        self.max_steps = max_steps
        self.delta_converged = delta_converged
        self.batch_size = batch_size
        self.cur_steps = 0
        self.W = None
        self.b = None

    def fit(self, X : np.array, Y : np.array):
        
        self.W = np.array([1.0]*X.shape[1])
        self.b = 1
        
        while(self.cur_steps <= self.max_steps):
            
            indexes = np.random.choice(np.arange(X.shape[0]), size = self.batch_size)
            X_sample = X[indexes]
            Y_sample = Y[indexes]
           
            B = (X_sample.dot(self.W) + self.b) - Y_sample
            grad_W = 2*X_sample.T.dot(B)/self.batch_size + 2*self.regularization*self.W
            grad_b = np.sum(2*B)/self.batch_size
            self.W -= self.lr*grad_W
            self.b -= self.lr*grad_b
            
            if(np.linalg.norm(self.lr*grad_W) <= self.delta_converged):
                return self
                
            self.cur_steps += 1
            
        return self
        
    def predict(self, X):

        return X.dot(self.W) + self.b
    
