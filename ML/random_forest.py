import numpy as np
import enum

class NodeType(enum.Enum):
    REGULAR = 1
    TERMINAL = 2

class MyRandomForestClassifier:
    """
    Data-diverse ensemble of tree calssifiers
    """
    big_number = 1 << 32

    def __init__(
            self,
            n_estimators: int,
            max_depth: tp.Optional[int] = None,
            min_samples_split: tp.Optional[int] = 2,
            seed: int = 0
    ):
        """
        :param n_estimators: number of trees in forest
        :param max_depth: maximal depth of tree, prevents overfitting
        :param min_samples_split: minimal amount of samples for node to be a splitter node
        :param seed: seed for RNG, enables reproducibility
        """
        self._n_classes = 0
        self._is_trained = False
        self.rng = np.random.default_rng(seed)
        self.estimators = [
            MyDecisionTreeClassifier(max_depth, min_samples_split, seed=seed) for
            seed in self.rng.choice(max(MyRandomForestClassifier.big_number, n_estimators), size=(n_estimators,),
                                    replace=False)]

    def _bootstrap_sample(self, X: np.ndarray, y: np.ndarray):
        """
        returns bootstrapped sample from X of equal size
        :param X: objects collection to sample from
        :param y: corresponding labels
        :return:
        """
        indices = np.random.choice(len(X), len(X), replace=True)
        return X[indices], y[indices]

    def fit(self, X: np.ndarray, y: np.ndarray):
        """
        fits each estimator of the ensemble on the bootstrapped data sample
        :param X: Data
        :param y: labels
        :return: fitted self
        """
        self._n_classes = np.unique(y).shape[0]
        for estimator in self.estimators:
            X_sample, y_sample = self._bootstrap_sample(X, y)
            estimator.fit(X_sample, y_sample)
        self._is_trained = True
        return self

    def predict_proba(self, X: np.ndarray):
        """
        predict probability of each class by averaging over all base estimators
        :param X: Data
        :return: array of probabilities
        """
        probas = np.zeros((X.shape[0], self._n_classes))
        for estimator in self.estimators:
            probas += estimator.predict_proba(X)
            
        probas /= len(self.estimators)
        
        return probas

    def predict(self, X):
        """
        predict class for each object
        :param X: Data
        :return: array of class labels
        """
        probs = self.predict_proba(X)
        return np.argmax(probs, axis=1)
