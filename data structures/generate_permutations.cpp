vector<vector<int>> generate_permutation(int n) {
    if (n == 1) {
        return {{1}};
    }
    auto v = generate_permutation(n - 1);
    vector<vector<int>> result;
    for (auto vec : v) {
        // n ways to insert n in vec
        for (int i = 0; i < vec.size(); i++) {
            vector<int> tmp;
            for (int j = 0; j < vec.size(); j++) {
                if (j == i) tmp.push_back(n);
                tmp.push_back(vec[j]);
            }
            result.push_back(tmp);
        }
        vector<int> tmp = vec;
        tmp.push_back(n);
        result.push_back(tmp);
    }
    return result;
}
