// link : https://codeforces.com/problemset/problem/652/D?locale=en

#include <iostream>
#include<math.h>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <deque>
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>
#include <thread>
#include <chrono>
#include <iomanip>  
typedef long long ll;
using namespace std;

const ll mod = 998244353;
const ll inf = 2e18;
 
int bitcount(ll n) { return n == 0 ? 0 : bitcount(n & (n - 1)) + 1;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
ll binexp(ll a, ll b){
    if (!b) return 1;
    ll res = binexp(a, b/2);
    res = (res*res)%mod;
    if(b%2) res = (res*a)%mod;
    return res;
}
ll rev(ll x) {return binexp(x, mod - 2);}

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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<tuple<int, int, int>> segments(n);
    vector<int> values;
    set<int> f;
    map<int, int> shrink;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        segments[i] = {x, y, i};
        f.insert(y);
    }
    for (auto x : f) values.push_back(x);
    for (int i = 0; i < values.size(); i++) shrink[values[i]] = i;
    sort(segments.begin(), segments.end());
    reverse(segments.begin(), segments.end());
    vector<int> ans(n, 0);
    fenwick fw(n);
    for (auto [x, y, index] : segments) {
        int i = shrink[y];
        ans[index] = fw.get(i);
        fw.inc(i, 1);
    }
    for (int i = 0; i < n; i++) cout << ans[i] << endl;
}
