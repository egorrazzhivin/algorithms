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

    int find(int v, int l_seg, int r_seg, int l, int k) {
        // find k'th 1 on segment [l, n]
        if (l > 1) k += get(v, l_seg, r_seg, 1, l - 1); // shift so find k'th 1 on [1, n]
        return find_prefix(v, l_seg, r_seg, k);
    }

    int find_prefix(int v, int l_seg, int r_seg, int k) {
        // find k'th 1 on segment [1, n]
        if (l_seg == r_seg) {
            // found
            return l_seg;
        }
        int m = (l_seg + r_seg) >> 1;
        int l_value = t[v << 1], r_value = t[v << 1 | 1];
        if (l_value >= k) return find_prefix(v << 1, l_seg, m, k);
        else return find_prefix(v << 1 | 1, m + 1, r_seg, k - l_value);
    }
};

// st.build(1, 1, n, a); a - 1-indexed
// st.get(1, 1, n, l, r)
