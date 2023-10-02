/*
n groups, for each of them:
c_i, w_i, k_i <= 10^9 - (cost, weight, number of objects of this type)
O(n * W) time complexity (n - size of groups, W - size of bag)
O(W) memory complexity
there is an easier solution in O(n * W * log(W)) 
using adding powers of twos for every group
(thus number of objects increasing in log(W) times
and then we're doing simple 0-1 knapsack)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

int main() {
    int size, total;
    std::cin >> size >> total;
    std::vector<int64_t> weight(size + 1), cost(size + 1), cnt(size + 1);
    for (int i = 1; i <= size; ++i) {
        std::cin >> weight[i] >> cost[i] >> cnt[i];
    }
    std::vector<int64_t> dp(total + 1, 0);
    std::deque<std::pair<int64_t, int>> dq;
    for (int element = 1; element <= size; ++element) {
        if (weight[element] > total) {
            continue;
        }
        std::vector<int64_t> new_dp(total + 1, 0);
        for (int reminder = 0; reminder < weight[element]; ++reminder) {
            int start = reminder;
            new_dp[start] = dp[start];
            dq.clear();
            dq.push_back(std::make_pair(new_dp[start], start));
            int64_t add = cost[element];
            while (start <= total) {
                start += weight[element];
                if (start > total) {
                    break;
                }
                int last_index = dq.front().second;
                if (static_cast<int64_t>(start - last_index) / weight[element] > cnt[element]) {
                    dq.pop_front();
                }
                int64_t new_value = dp[start] - add;
                while (!dq.empty() && dq.back().first < new_value) {
                    dq.pop_back();
                }
                dq.push_back(std::make_pair(new_value, start));
                int64_t max_value = dq.front().first;
                new_dp[start] = max_value + add;
                add += cost[element];
            }
        }
        for (int we = 1; we <= total; ++we) {
            new_dp[we] = std::max(new_dp[we], new_dp[we - 1]);
        }
        dp = new_dp;
    }
    std::cout << dp[total] << '\n';
}
