/*
https://cses.fi/problemset/task/1139/
interesting euler tour + bit
*/

#include <iostream>
#include <math.h>
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
typedef long long ll;
using namespace std;
 
const ll mod = 1e9+7;
const ll inf = 1e18+1e17;
 
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
    vector<ll> f;

    fenwick(int n){
        f.assign(n+1,0);
    }

    void inc(int pos, ll val){
        for(int i = pos; i<(int)f.size(); i=(i|(i+1))){
            f[i] += val;
        }
    }

    ll get(int r){
        ll res = 0;
        for(int i =r; i>=0; i=(i&(i+1))-1){
            res+=f[i];
        }

        return res;
    }

    ll get(int l, int r) {
        return get(r) - get(l-1);
    }
};

vector<vector<int>> g(200200);
vector<int> lend(200200), tour(200200), color(200200), ans(200200); 
int t = 0;

/*
 * tour = euler tour
 * color = color of each node
 * answer = answer for each node
 * lend = left endpoint of each node for BIT
 */

void dfs(int v,int par){
    lend[v] = t;
    for(auto to : g[v]){
        if(to!=par) dfs(to,v);
    }
    tour[t] = v;
    t++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i =1;i<=n;i++) cin >> color[i];
    for(int i =0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    fenwick fw(n);
    map<int,int> last_color; //rightmost occur of each color
    for(int i =0;i<n;i++){
        // i is the current vertex in euler tour
        //lend[i] - end of the i's subtree
        //
        if(last_color.count(color[tour[i]])){
            fw.inc(last_color[color[tour[i]]],-1);
        }
        last_color[color[tour[i]]] = i;
        fw.inc(i, 1);
        ans[tour[i]] = fw.get(i) - fw.get(lend[tour[i]]-1);
    }
    for(int i =1;i<=n;i++) cout << ans[i] << " ";

}
