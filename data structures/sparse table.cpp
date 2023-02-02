/*
great task from codeforces on sparse table
https://codeforces.com/contest/1709/problem/D
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
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    int q;
    cin >> q;
    int p = 0;
    while ((1 << p) <= m)p++;
    p--;
    vector<vector<int>> table(p+1, vector<int>(m));
    for (int i = 0; i < m; i++) table[0][i] = a[i];
    for (int i = 1; i <= p; i++) {
        for (int j = 0; j + (1 << i) <= m; j++) {
            table[i][j] = max(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
        }
    }
    vector<int> log(m + 1);
    log[0] = log[1] = 0;
    for (int i = 2; i <= m; i++) {
        log[i] = log[i / 2] + 1;
    }
    while (q--) {
        int xs, ys, xf, yf, k;
        cin >> xs >> ys >> xf >> yf >> k;
        xs--, ys--, xf--, yf--;
        if (abs(xs - xf) % k != 0 || abs(ys - yf) % k != 0) {
            cout << "NO" << endl;
            continue;
        }
        if (ys == yf) {
            cout << "YES" << endl;
            continue;
        }

        if (ys > yf) swap(ys, yf);
        int mxy = (n - 1 - xs) / k * k + xs+1;
        int diff = log[yf - ys + 1];
        int mxm = max(table[diff][ys], table[diff][yf - (1 << diff)+1]);
        
        //cout << "max available = " << mxy << " max height = " << mxm << endl;
        if (mxm < mxy) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
