struct segtree {
    int n;
    vector<int64_t> t;

    segtree(int n) {
        t.assign(4 * n + 5, 0);
    }

    void build(int v, int l, int r, vector<int64_t>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(v << 1, l, m, a);
        build(v << 1 | 1, m + 1, r, a);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    }

    void update(int v, int l_seg, int r_seg, int index, int64_t x) {
        if (l_seg == r_seg) {
            t[v] = x;
            return;
        }
        int m = (l_seg + r_seg) >> 1;
        if (index <= m) update(v << 1, l_seg, m, index, x);
        else update(v << 1 | 1, m + 1, r_seg, index, x);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    }

    int64_t get(int v, int l_seg, int r_seg, int l, int r) {
        if (l_seg > r || r_seg < l) return -inf;
        if (l_seg >= l && r_seg <= r) return t[v];
        int m = (l_seg + r_seg) >> 1;
        return max(get(v << 1, l_seg, m, l, r), get(v << 1 | 1, m + 1, r_seg, l, r));
    }

    int find_l_whole(int v, int l_seg, int r_seg, int64_t x) {
        // on [l_seg, r_seg] find leftmost i: a[i] > x
        if (l_seg == r_seg) {
            if (t[v] > x) return l_seg;
            else return -1; // no answer
        }
        int m = (l_seg + r_seg) >> 1;
        if (t[v << 1] > x) return find_l_whole(v << 1, l_seg, m, x); // go to left
        else return find_l_whole(v << 1 | 1, m + 1, r_seg, x); // go to right
    }

    int find_r_whole(int v, int l_seg, int r_seg, int64_t x) {
        // on [l_seg, r_seg] find rightmost i: a[i] > x
        if (l_seg == r_seg) {
            if (t[v] > x) return l_seg;
            else return -1; // no answer
        }
        int m = (l_seg + r_seg) >> 1;
        if (t[v << 1 | 1] > x) return find_r_whole(v << 1 | 1, m + 1, r_seg, x); // go to right
        else return find_r_whole(v << 1, l_seg, m, x); // go to left
    }

    int find_l(int v, int l_seg, int r_seg, int l, int64_t x) {
        // find leftmost i > l: a[i] > x
        if (r_seg < l) return -1;
        if (l <= l_seg) {
            if (t[v] > x) return find_l_whole(v, l_seg, r_seg, x); // if true then leftmost! (think)
            else return -1;
        }
        int m = (l_seg + r_seg) >> 1;
        int l_answer = find_l(v << 1, l_seg, m, l, x);
        if (l_answer != -1) return l_answer;
        else return find_l(v << 1 | 1, m + 1, r_seg, l, x);
    }

    int find_r(int v, int l_seg, int r_seg, int r, int64_t x) {
        // find rightmost i < r: a[i] > x
        if (l_seg > r) return -1;
        if (r_seg <= r) {
            if (t[v] > x) return find_r_whole(v, l_seg, r_seg, x); // if true then rightmost! (think)
            else return -1;
        }
        int m = (l_seg + r_seg) >> 1;
        int r_answer = find_r(v << 1 | 1, m + 1, r_seg, r, x);
        if (r_answer != -1) return r_answer;
        else return find_r(v << 1, l_seg, m, r, x);
    }
};

// NOT 100% sure but try
// st.build(1, 1, n, a); a - 1-indexed
// st.get(1, 1, n, l, r)
