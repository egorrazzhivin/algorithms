/*
https://atcoder.jp/contests/agc020/tasks/agc020_c
interesting bitset problem
*/
// reminder: i have autism

#include <iostream>
#include <bitset>
#include <algorithm>

typedef long long ll;
using namespace std;

const int mxn = 4e6+7;
bitset<mxn> f;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n;
    cin >> n;
    int sum = 0;
    f[0] = 1;
    while(n--){
        int x;
        cin >> x;
        sum += x;
        f |= (f<<x);
    }
    int find = (sum+1)/2;
    while(!f[find]) find++;
    cout << find << endl;
}

