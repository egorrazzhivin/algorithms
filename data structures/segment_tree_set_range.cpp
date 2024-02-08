struct segtree {
    int n;
    vector<int64_t> t;
    vector<int64_t> modify;
 
    segtree(int n) {
        t.assign(4 * n + 5, 0);
        modify.assign(4 * n + 5, -1);
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
 
    void push(int v, int l_seg, int r_seg) {
        if (modify[v] != -1) {
            t[v] = (r_seg - l_seg + 1) * modify[v];
            if (l_seg != r_seg) {
                modify[v << 1] = modify[v];
                modify[v << 1 | 1] = modify[v];
            }
            modify[v] = -1;
        }
    }
 
    void update(int v, int l_seg, int r_seg, int l, int r, int64_t x) {
        push(v, l_seg, r_seg);
        if (l <= l_seg && r >= r_seg) {
            modify[v] = x;
            push(v, l_seg, r_seg);
            return;
        }
        if (l > r_seg || r < l_seg) {
            return;
        }
        int m = (l_seg + r_seg) >> 1;
        update(v << 1, l_seg, m, l, r, x);
        update(v << 1 | 1, m + 1, r_seg, l, r, x);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }
 
    int64_t get(int v, int l_seg, int r_seg, int l, int r) {
        push(v, l_seg, r_seg);
        if (l_seg > r || r_seg < l) return 0;
        if (l_seg >= l && r_seg <= r) return t[v];
        int m = (l_seg + r_seg) >> 1;
        return get(v << 1, l_seg, m, l, r) + get(v << 1 | 1, m + 1, r_seg, l, r);
    }
};

// st.build(1, 1, n, a); a - 1-indexed
// st.get(1, 1, n, l, r)
