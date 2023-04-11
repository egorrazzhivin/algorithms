/*
link: https://cses.fi/problemset/task/1679/
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
typedef long long ll;
using namespace std;
 
const int mod = 1699997; //prime
const ll inf = 1e18;
 
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
 
bool cycle(int v, vector<vector<int>>& g, vector<int>& color){
    color[v] = 1;
    for(auto to : g[v]){
        if(color[to]==0){
            if(cycle(to, g,color)) return true;
        }
        else if (color[to]==1) return true;
    }
    color[v]=2;
    return false;
}

void dfs(int v,vector<vector<int>>& g, vector<bool>& used, vector<int>& way){
    used[v] = true;
    //cout << " v = " << v << endl;
    for(auto to : g[v]){
        if(!used[to]) {
            //cout << "to = " << to << endl;
            dfs(to,g,used,way);
        }
    }
    way.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    vector<int> in(n+1, -1);
    for(int i =0;i<m;i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    vector<bool> used(n+1, false);
    vector<int> color(n+1, 0);
    bool ok = false;
    for(int i =1;i<=n;i++){
        if(color[i]==0){
            if(cycle(i,g,color)) ok = true;
        }
    }
    if(ok) cout << "IMPOSSIBLE" << endl;
    else{
        vector<int> way;
        for(int i =1;i<=n;i++) if(!used[i])dfs(i,g,used,way);
        reverse(way.begin(), way.end());
        for(auto x : way) cout << x << " ";

    }
}   
