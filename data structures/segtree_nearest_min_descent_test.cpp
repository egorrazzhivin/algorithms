// how i tested this shit

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
        t[v] = min(t[v << 1], t[v << 1 | 1]);
    }

    void update(int v, int l_seg, int r_seg, int index, int64_t x) {
        if (l_seg == r_seg) {
            t[v] = x;
            return;
        }
        int m = (l_seg + r_seg) >> 1;
        if (index <= m) update(v << 1, l_seg, m, index, x);
        else update(v << 1 | 1, m + 1, r_seg, index, x);
        t[v] = min(t[v << 1], t[v << 1 | 1]);
    }

    int64_t get(int v, int l_seg, int r_seg, int l, int r) {
        if (l_seg > r || r_seg < l) return inf;
        if (l_seg >= l && r_seg <= r) return t[v];
        int m = (l_seg + r_seg) >> 1;
        return min(get(v << 1, l_seg, m, l, r), get(v << 1 | 1, m + 1, r_seg, l, r));
    }

    int find_l_whole(int v, int l_seg, int r_seg, int x) {
        // on [l_seg, r_seg] find leftmost i: a[i] < x
        if (l_seg == r_seg) {
            if (t[v] < x) return l_seg;
            else return -1; // no answer
        }
        int m = (l_seg + r_seg) >> 1;
        if (t[v << 1] < x) return find_l_whole(v << 1, l_seg, m, x); // go to left
        else return find_l_whole(v << 1 | 1, m + 1, r_seg, x); // go to right
    }

    int find_r_whole(int v, int l_seg, int r_seg, int x) {
        // on [l_seg, r_seg] find rightmost i: a[i] < x
        if (l_seg == r_seg) {
            if (t[v] < x) return l_seg;
            else return -1; // no answer
        }
        int m = (l_seg + r_seg) >> 1;
        if (t[v << 1 | 1] < x) return find_r_whole(v << 1 | 1, m + 1, r_seg, x); // go to right
        else return find_r_whole(v << 1, l_seg, m, x); // go to left
    }

    int find_l(int v, int l_seg, int r_seg, int l, int x) {
        // find leftmost i > l: a[i] < x
        if (r_seg < l) return -1;
        if (l <= l_seg) {
            if (t[v] < x) return find_l_whole(v, l_seg, r_seg, x); // if true then leftmost! (think)
            else return -1;
        }
        int m = (l_seg + r_seg) >> 1;
        int l_answer = find_l(v << 1, l_seg, m, l, x);
        if (l_answer != -1) return l_answer;
        else return find_l(v << 1 | 1, m + 1, r_seg, l, x);
    }

    int find_r(int v, int l_seg, int r_seg, int r, int x) {
        // find rightmost i < r: a[i] < x
        if (l_seg > r) return -1;
        if (r_seg <= r) {
            if (t[v] < x) return find_r_whole(v, l_seg, r_seg, x); // if true then rightmost! (think)
            else return -1;
        }
        int m = (l_seg + r_seg) >> 1;
        int r_answer = find_r(v << 1 | 1, m + 1, r_seg, r, x);
        if (r_answer != -1) return r_answer;
        else return find_r(v << 1, l_seg, m, r, x);
    }
};

// st.build(1, 1, n, a); a - 1-indexed
// st.get(1, 1, n, l, r)

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

int main() {
    int n;
    cin >> n;
    auto v = generate_permutation(n);
    int all_cases = v.size();
    int good_cases = 0;
    for (auto vec : v) {
        vector<int> a(n + 2, 0);
        for (int i = 1; i <= n; i++) {
            a[i] = vec[i - 1];
        }
        vector<int> l(n + 1, 0), r(n + 1, n + 1);
        vector<int> l_stack, r_stack;
        l_stack.push_back(1);
        for (int i = 2; i <= n; i++) {
            while (!l_stack.empty() && a[l_stack.back()] > a[i]) {
                l_stack.pop_back();
            }
            if (!l_stack.empty()) {
                l[i] = l_stack.back();
            }
            l_stack.push_back(i);
        }
        r_stack.push_back(n);
        for (int i = n - 1; i >= 1; i--) {
            while (!r_stack.empty() && a[r_stack.back()] > a[i]) {
                r_stack.pop_back();
            }
            if (!r_stack.empty()) {
                r[i] = r_stack.back();
            }
            r_stack.push_back(i);
        }
        segtree st(n);
        st.build(1, 1, n, a);
        vector<int> l_st(n + 1, 0), r_st(n + 1, n + 1);
        for (int i = 1; i <= n; i++) {
            int new_r = st.find_l(1, 1, n, i + 1, a[i]);
            if (new_r == -1) new_r = n + 1;
            int new_l = st.find_r(1, 1, n, i - 1, a[i]);
            if (new_l == -1) new_l = 0;
            l_st[i] = new_l;
            r_st[i] = new_r;
        }
        if (l == l_st && r == r_st) good_cases++;
    }
    cout << good_cases << " / " << all_cases << " are good!" << endl;
}
