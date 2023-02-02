/*
cool problem on bitmasks from codeforces
https://codeforces.com/contest/1778/problem/C
*/

#include <iostream>
#include<math.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
typedef long long ll;
using namespace std;
//ios::sync_with_stdio(false);
 
 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string a, b;
        cin >> a;
        cin >> b;
        vector<char> noteq;
        vector<bool> used(27, false);
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i] && used[a[i] - 'a'] == false) {
                noteq.push_back(a[i]);
                used[a[i] - 'a'] = true;
            }
        }
        ll ans = 0;
        ll cur = 0;
        for (int mask = 0; mask <= (1 << noteq.size()); mask++) {
            set<char> add;
            int p = 0;
            for (int i = 0; i < noteq.size(); i++) {
                if (mask & (1 << i))p++;
            }
            if (p <= k) {
                for (int i = 0; i < noteq.size(); i++) {
                    if (mask & (1 << i)) {
                        add.insert(noteq[i]);
                    }
                }
                cur = 0;
                string s = a;
                for (int i = 0; i < n; i++) {
                    if (s[i] != b[i]) {
                        if (add.count(s[i])) {
                            s[i] = b[i];
                        }
                    }
                }
                int l = 0;
                int counter = 0;
                while (l < n) {
                    if (s[l] == b[l]) {
                        counter++;
                        cur += counter;
                        l++;
                    }
                    else {
                        counter = 0;
                        l++;
                    }
                }
                ans = max(ans, cur);
            }
        }
        cout << ans << endl;
    }
}
