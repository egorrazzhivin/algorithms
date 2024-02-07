struct fenwick{
    vector<vector<vector<int64_t>>> fw;

    explicit fenwick(int size) {
        fw = vector<vector<vector<int64_t>>>(size,
             vector<vector<int64_t>>(size, vector<int64_t>(size, 0)));
    }

    void inc(int x, int y, int z, int val) {
        for (int i = x; i < static_cast<int>(fw.size()); i = (i | (i + 1))) {
            for (int j = y; j < static_cast<int>(fw.size()); j = (j | (j + 1))) {
                for (int l = z; l < static_cast<int>(fw.size()); l = (l | (l + 1))) {
                    fw[i][j][l] += val;
                }
            }
        }
    }

    int64_t get(int x, int y, int z) {
        int64_t res = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                for (int l = z; l >= 0; l = (l & (l + 1)) - 1) {
                    res += fw[i][j][l];
                }   
            }
        }
        return res;
    }

    int64_t get(int x1, int y1, int z1, int x2, int y2, int z2) {
        return get(x2, y2, z2) - get(x2, y2, z1 - 1) - get(x1 - 1, y2, z2) -
               get(x2, y1 - 1, z2) + get(x1 - 1, y1 - 1, z2) + get(x1 - 1, y2, z1 - 1) +
               get(x2, y1 - 1, z1 - 1) - get(x1 - 1, y1 - 1, z1 - 1);
    }
};
