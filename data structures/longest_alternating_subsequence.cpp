//nice dp problem

#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    int sz;
    std::cin >> sz;

    std::vector<int> fu(sz+1, 0);
    for (int i = 1; i <= sz; ++i) {
        std::cin >> fu[i];
    }
    std::vector<std::vector<int>> dp(sz+1, std::vector<int>(2, 0));
    std::vector<std::vector<int>> par(sz+1, std::vector<int>(2, -1));
    dp[sz][0] = dp[sz][1] = 1;
    for (int ii = sz - 1; ii >= 1; --ii) {
        for (int jj = ii + 1; jj <= sz; ++jj) {
            if (fu[jj] < fu[ii]) {
                if (dp[jj][0] + 1 > dp[ii][1]) {
                    dp[ii][1] = dp[jj][0] + 1;
                    par[ii][1] = jj;
                }
            }
            else if (fu[jj] > fu[ii]) {
                if (dp[jj][1] + 1 > dp[ii][0]) {
                    dp[ii][0] = dp[jj][1] + 1;
                    par[ii][0] = jj;
                }
            }
        }
        if (dp[ii][0] == 0) {
            dp[ii][0] = 1;
        }
        if (dp[ii][1] == 0) {
            dp[ii][1] = 1;
        }
    }
    int max_length_up = 0, max_length_down = 0;
    int type_up = -1, type_down = -1, start_up = -1, start_down = -1;
    for (int i = 1; i <= sz; ++i) {
        if (dp[i][0] > max_length_down) {
            max_length_down = dp[i][0];
            start_down = i;
            type_down = 0;
        }
        if (dp[i][1] > max_length_up) {
            max_length_up = dp[i][1];
            start_up = i;
            type_up = 1;
        }
    }
    std::vector<int> down, up;
    while (start_down != -1) {
        down.push_back(start_down);
        start_down = par[start_down][type_down];
        type_down ^= 1;
    }
    while (start_up != -1) {
        up.push_back(start_up);
        start_up = par[start_up][type_up];
        type_up ^= 1;
    }
    int size_up = up.size();
    int size_down = down.size();
    if (size_up > size_down) {
        for (auto x : up) {
            std::cout << fu[x] << " ";
        }
    } else if (size_down > size_up) {
        for (auto x : down) {
            std::cout << fu[x]  << " ";
        }
    } else {
        int choose_up = 0;
        for (int i = 0; i < size_up; ++i) {
            if (up[i] == down[i]) {
                continue;
            }
            if (up[i] < down[i]) {
                choose_up = 1;
                break;
            }
        }
        if (choose_up) {
            for (auto x : up) {
                std::cout << fu[x] << " ";
            }
        } else {
            for (auto x : down) {
                std::cout << fu[x] << " ";
            }
        }
    }
    return 0;
}
