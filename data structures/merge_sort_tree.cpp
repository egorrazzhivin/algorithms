struct segtree {
    int n;
    vector<vector<int64_t>> t;

    segtree(int n) {
        t.assign(4 * n + 5, vector<int64_t>());
    }

    vector<int64_t> merge(vector<int64_t>& left, vector<int64_t>& right) {
        vector<int64_t> result;
        int l = 0, r = 0;
        while (l < left.size() && r < right.size()) {
            if (left[l] <= right[r]) {
                result.push_back(left[l]);
                l++;
            } else {
                result.push_back(right[r]);
                r++;
            }
        }
        if (l == left.size()) {
            while (r < right.size()) {
                result.push_back(right[r]);
                r++;
            }
        } else {
            while (l < left.size()) {
                result.push_back(left[l]);
                l++;
            }
        }
        return result;
    }

    void build(int v, int l, int r, vector<int>& a) {
        if (l == r) {
            t[v] = {a[l]};
            return;
        }
        int m = (l + r) >> 1;
        build(v << 1, l, m, a);
        build(v << 1 | 1, m + 1, r, a);
        t[v] = merge(t[v << 1], t[v << 1 | 1]);
    }

    int64_t get(int v, int l_seg, int r_seg, int l, int r, int x) {
        // return number of elements <= x
        if (l_seg > r || r_seg < l) return 0;
        if (l_seg >= l && r_seg <= r) {
            int f = upper_bound(t[v].begin(), t[v].end(), x) - t[v].begin();
            return f; // not 100% sure but try
        }
        int m = (l_seg + r_seg) >> 1;
        return get(v << 1, l_seg, m, l, r, x) + get(v << 1 | 1, m + 1, r_seg, l, r, x);
    }
};

// st.build(1, 1, n, a); a - 1-indexed
// st.get(1, 1, n, l, r)
