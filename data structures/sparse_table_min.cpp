const int LOG = 20;

struct sparse_table {
    // min sparse table
    int n;
    vector<vector<int>> sparse;

    sparse_table(int n) :
        n(n),
        sparse(vector<vector<int>>(LOG, vector<int>(n + 1, 0))) {}

    void build(vector<int>& a) {
        for (int i = 1; i <= n; i++) {
            sparse[0][i] = a[i];
        }
        for (int sz = 1; sz <= 19; sz++) {
            for (int i = 1; i + (1 << sz) - 1 <= n; i++) {
                sparse[sz][i] = min(sparse[sz - 1][i], sparse[sz - 1][i + (1 << (sz - 1))]);
            }
        }
    }

    int get(int l, int r) {
        int f = 1;
        int dist = r - l + 1;
        int log = 0;
        while (f <= dist) {
            f *= 2;
            log++;
        }
        log--;
        f /= 2;
        int res = min(sparse[log][l], sparse[log][r - f + 1]);
        return res;
    }
};
