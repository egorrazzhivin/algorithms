struct segtree {
    int n;
    vector<int64_t> t;
    vector<vector<pair<int64_t, int>>> modify;
 
    segtree(int n) {
        t.assign(4 * n + 5, 0);
        modify = vector<vector<pair<int64_t, int>>>(4 * n + 5);
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
        if (!modify[v].empty()) {
            bool has_one = false; // for set
            int last_one = -1;
            for (int i = 0; i < modify[v].size(); i++) {
                if (modify[v][i].second == 1) {
                    has_one = true;
                    last_one = i;
                }
            }
            bool child = (l_seg != r_seg);
            if (!has_one) {
                for (auto [x, c] : modify[v]) {
                    if (child) {
                        modify[v << 1].push_back({x, c});
                        modify[v << 1 | 1].push_back({x, c});
                    }
                    t[v] += (r_seg - l_seg + 1) * x;
                }
                modify[v].clear();
            } else {
                if (child) {
                    modify[v << 1].clear();
                    modify[v << 1 | 1].clear();
                }
                for (int i = last_one; i < modify[v].size(); i++) {
                    auto [x, c] = modify[v][i];
                    if (child) {
                        modify[v << 1].push_back({x, c});
                        modify[v << 1 | 1].push_back({x, c});
                    }
                    if (c == 1) t[v] = (r_seg - l_seg + 1) * x;
                    else t[v] += (r_seg - l_seg + 1) * x;
                }
                modify[v].clear();
            }
        }
    }
 
    void update_sum(int v, int l_seg, int r_seg, int l, int r, int x) {
        push(v, l_seg, r_seg);
        if (l <= l_seg && r >= r_seg) {
            modify[v].push_back({x, 2});
            push(v, l_seg, r_seg);
            return;
        }
        if (l > r_seg || r < l_seg) {
            return;
        }
        int m = (l_seg + r_seg) >> 1;
        update_sum(v << 1, l_seg, m, l, r, x);
        update_sum(v << 1 | 1, m + 1, r_seg, l, r, x);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }

    void update_set(int v, int l_seg, int r_seg, int l, int r, int x) {
        push(v, l_seg, r_seg);
        if (l <= l_seg && r >= r_seg) {
            modify[v].push_back({x, 1});
            push(v, l_seg, r_seg);
            return;
        }
        if (l > r_seg || r < l_seg) {
            return;
        }
        int m = (l_seg + r_seg) >> 1;
        update_set(v << 1, l_seg, m, l, r, x);
        update_set(v << 1 | 1, m + 1, r_seg, l, r, x);
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
