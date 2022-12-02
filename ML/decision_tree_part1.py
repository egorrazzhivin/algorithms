def H(R: pd.DataFrame) -> float:
    #compute impurity criterion for a fixed set of objects R.
    #cast column is assumed to contain target value
    
    return np.var(R['target']) #for regression task our criterion is std
                        
def split_node(R_m: pd.DataFrame, feature: str, t: float) -> Iterable[np.array]:
    #split a fixed set of objects R_m given feature number and threshold t
    
    X_left = R_m[R_m[feature] <= t]
    X_right = R_m[R_m[feature] > t]
    
    return [X_left, X_right]

def q_error(R_m: pd.DataFrame, feature: str, t: float) -> float:
    #Compute error criterion for given split parameters
    
    X_left, X_right = split_node(R_m, feature, t)
    h_left, h_right = H(X_left), H(X_right)
    error = X_left.shape[0]/R_m.shape[0] * h_left + X_right.shape[0]/R_m.shape[0] * h_right
    
    return error
