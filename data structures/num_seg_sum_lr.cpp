/*
  finding number of segments (l,r) 
  such that sum(l, r) < target
  link: https://codeforces.com/contest/1042/problem/D?locale=en
*/

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

const ll mod = 1e9+7;
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
        for (int i = right; i >= 0; i = (i & (i + 1)) - 1) {
            res += fw[i];
        }
        return res;
    }

    int64_t get(int left, int right) {
        return get(right) - get(left - 1);
    }
};

ll solve(vector<pair<ll, ll>>& all, ll target) {
    // find (l,r) such that sum(l, r) < target
    int n = all.size();
    ll result = 0;
    fenwick fw(n);
    set<pair<ll, ll>> values;
    set<pair<ll, ll>> high;
    for (int i = 0; i < n; i++) {
        high.insert(all[i]);
        if (all[i].first - all[0].first < target) {
            values.insert(all[i]);
            high.erase(all[i]);
            fw.inc(all[i].second, 1);
        }
    }
    for (int i = 0; i < n; i++) {
        result += fw.get(all[i].second, n - 1);
        if (i == n - 1) break;
        ll next = all[i + 1].first;
        while(!high.empty() && (high.begin()->first - next) < target) {
            values.insert(*high.begin());
            fw.inc(high.begin()->second, 1);
            high.erase(high.begin());
        }
    }
    if (target > 0) result -= n;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll t;
    cin >> t;
    vector<ll> a(n), pref(n + 1, 0);
    vector<pair<ll, ll>> all(n + 1);
    all[0] = make_pair(1ll * 0, 1ll * 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
        all[i] = make_pair(pref[i + 1], i + 1);
    }
    sort(all.begin(), all.end());
    ll ans = solve(all, t);
    cout << ans << '\n';
}
