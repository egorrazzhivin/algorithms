/*
  finding kth element in sliding window in O(logN) per query
  using fenwick tree
*/

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <string>

struct fenwick{
    std::vector<int64_t> fw;

    explicit fenwick(int size) {
        fw.assign(size, 0);
    }

    void inc(int pos, int64_t val) {
        for (int i = pos; i < static_cast<int>(fw.size()); i = (i | (i+1))) {
            fw[i] += val;
        }
    }

    int64_t get(int right) {
        int64_t res = 0;
        for (int i = right; i >= 0; i = (i & (i+1)) - 1) {
            res += fw[i];
        }
        return res;
    }

    int64_t get(int left, int right) {
        return get(right) - get(left - 1);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int size, len, kth;
    std::cin >> size >> len >> kth;
    std::vector<std::pair<int, int>> elements(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> elements[i].first;
        elements[i].second = i;
    }
    std::sort(elements.begin(), elements.end());
    std::vector<int> compressed(size, -1);
    std::vector<std::vector<int>> remember(size);
    int value = 0;
    int pointer = 0;
    while (pointer < size) {
        if (pointer == 0) {
            compressed[value] = elements[pointer].first;
            remember[value].emplace_back(elements[pointer].second);
        } else {
            if (elements[pointer].first == elements[pointer - 1].first) {
                remember[value].emplace_back(elements[pointer].second);
            } else {
                ++value;
                compressed[value] = elements[pointer].first;
                remember[value].emplace_back(elements[pointer].second);
            }
        }
        ++pointer;
    }
    std::vector<int> new_elements(size, -1);
    for (int index = 0; index < size; ++index) {
        for (auto val : remember[index]) {
            new_elements[val] = index;
        }
    }
    std::string queries;
    std::cin >> queries;
    fenwick fw(size);
    fw.inc(new_elements[0], 1);
    int left = 0, right = 0;
    for (int index = 0; index < len; ++index) {
        if (queries[index] == 'L') {
            fw.inc(new_elements[left], -1);
            ++left;
        } else {
            ++right;
            fw.inc(new_elements[right], 1);
        }
        if (right - left + 1 < kth) {
            std::cout << -1 << '\n';
            continue;
        }
        int le = 0, ri = size - 1;
        int ans = ri;
        while (le <= ri) {
            int mid = (le + ri) >> 1;
            if (fw.get(mid) >= kth) {
                ans = mid;
                ri = mid - 1;
            } else {
                le = mid + 1;
            }
        }
        std::cout << compressed[ans] << '\n';
    }
}
