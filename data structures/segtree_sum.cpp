struct segtree {
    int n;
    vector<int64_t> t;

    segtree(int n) {
        t.assign(4 * n + 5, 0);
    }

    void build(int v, int l, int r, vector<int>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        // [l, m], [m + 1, r];
        build(v << 1, l, m, a);
        build(v << 1 | 1, m + 1, r, a);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }

    void update(int v, int l_seg, int r_seg, int index, int x) {
        if (l_seg == r_seg) {
            t[v] = x;
            return;
        }
        int m = (l_seg + r_seg) >> 1;
        if (index <= m) update(v << 1, l_seg, m, index, x);
        else update(v << 1 | 1, m + 1, r_seg, index, x);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }

    int64_t get(int v, int l_seg, int r_seg, int l, int r) {
        if (l_seg > r || r_seg < l) return 0;
        if (l_seg >= l && r_seg <= r) return t[v];
        int m = (l_seg + r_seg) >> 1;
        return get(v << 1, l_seg, m, l, r) + get(v << 1 | 1, m + 1, r_seg, l, r);
    }
};
