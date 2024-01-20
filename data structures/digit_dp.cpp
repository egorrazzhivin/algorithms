// https://atcoder.jp/contests/abc336/tasks/abc336_e

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    /*
        for fixed sum of digits let's find all numbers
        of length len (including leading zeros) so that they are divisible by their sum
    */
    ll k;
    cin >> k;
    vector<int> digits;
    while (k) {
        digits.push_back(k % 10);
        k /= 10;
    }
    reverse(digits.begin(), digits.end());
    ll ans = 0;
    for (int sum = 1; sum < 150; sum++) {
        /*
        dp[len][current_sum][rem][tight];
        */
        vector<vector<vector<vector<ll>>>> dp(digits.size() + 1,
        vector<vector<vector<ll>>>(sum + 1, vector<vector<ll>>(sum + 1, vector<ll>(2, 0))));

        dp[0][0][0][1] = 1;

        for (int len = 0; len < digits.size(); len++) {
            // push dp
            for (int current_sum = 0; current_sum <= sum; current_sum++) {
                for (int reminder = 0; reminder < sum; reminder++) {
                    for (int tight = 0; tight <= 1; tight++) {
                        // we at dp[len][current_sum][reminder][tight]
                        // want to add something
                        for (int add = 0; add <= 9; add++) {
                            if (current_sum + add <= sum) {
                                int new_reminder = (reminder * 10 + add) % sum;
                                if (tight == 0) {
                                    dp[len + 1][current_sum + add][new_reminder][0] += dp[len][current_sum][reminder][0];
                                } else {
                                    if (add < digits[len]) {
                                        dp[len + 1][current_sum + add][new_reminder][0] += dp[len][current_sum][reminder][1];
                                    } else if (add == digits[len]) {
                                        dp[len + 1][current_sum + add][new_reminder][1] += dp[len][current_sum][reminder][1];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        ans += dp[digits.size()][sum][0][0] + dp[digits.size()][sum][0][1];
    }
    cout << ans << endl;
}
