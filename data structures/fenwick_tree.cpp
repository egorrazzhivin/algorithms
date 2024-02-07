struct fenwick{
    std::vector<int64_t> fw;

    explicit fenwick(int size) {
        fw.assign(size, 0);
    }

    void inc(int pos, int64_t val) {
        for (int i = pos; i < static_cast<int>(fw.size()); i = (i | (i + 1))) {
            fw[i] += val;
        }
    }

    int64_t get(int right) {
        int64_t res = 0;
        for (int i = right; i >= 0; i = (i & (i + 1)) - 1) {
            res += fw[i];
        }
        return res;
    }

    int64_t get(int left, int right) {
        return get(right) - get(left - 1);
    }
};
