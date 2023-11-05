import numpy as np
def gini(y: np.ndarray) -> float:
    """
    Computes Gini index for given set of labels
    :param y: labels
    :return: Gini impurity
    """
    unique_classes, class_counts = np.unique(y, return_counts=True)
    
    class_probabilities = class_counts / len(y)
  
    gini_index = 1 - np.sum(class_probabilities**2)


    return gini_index

import typing as tp
def weighted_impurity(y_left: np.ndarray, y_right: np.ndarray) -> \
        tp.Tuple[float, float, float]:
    """
    Computes weighted impurity by averaging children impurities
    :param y_left: left  partition
    :param y_right: right partition
    :return: averaged impurity, left child impurity, right child impurity
    """
    n_left = len(y_left)
    n_right = len(y_right)
    
    left_impurity = gini(y_left)
    right_impurity = gini(y_right)
    
    weighted_impurity = (n_left * left_impurity + n_right * right_impurity) / (n_left + n_right)

    return weighted_impurity, left_impurity, right_impurity
