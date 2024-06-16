// please be patient i have autism

#include <iostream>
#include<math.h>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <deque>
#include <memory>
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>
#include <thread>
#include <chrono>
#include <iomanip>  

using namespace std;

const int64_t bound = 1e9 + 7;
const int64_t mod = 1e9 + 7;
const int64_t inf = 1e18;

vector<vector<int64_t>> matrix_multiply(vector<vector<int64_t>> A, vector<vector<int64_t>> B, int64_t MOD = mod) {
    // square matrices
    int n = A.size();
    vector<vector<int64_t>> result(n, vector<int64_t>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
            }
        }
    }
    return result;
}

vector<vector<int64_t>> matrix_binexp(vector<vector<int64_t>> A, int64_t power, int64_t MOD = mod) {
    int n = A.size();
    vector<vector<int64_t>> E(n, vector<int64_t>(n, 0));
    for (int i = 0; i < n; i++) {
        E[i][i] = 1;
    }
    if (power == 0) return E;
    auto result = matrix_binexp(A, power / 2, MOD);
    result = matrix_multiply(result, result, MOD);
    if (power % 2) result = matrix_multiply(result, A, MOD);
    return result;
}

int main() {
    vector<vector<int64_t>> A = {{1, 1}, {1, 0}};
    auto result = matrix_binexp(A, 5);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << " i = " << i << " j = " << j << " result = " << result[i][j] << endl;
        }
    }
    // max number in matrix is power + 1 th Fib number in 0-indexation
    // power = 5 max number is 8 which is 6th 0-indexed fib bro
}
