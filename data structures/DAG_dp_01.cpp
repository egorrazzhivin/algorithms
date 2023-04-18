/*
link: https://codeforces.com/contest/1679/problem/D
DAG_dp + binary search
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

bool cycle(int v, vector<int>& color, vector<vector<int>>& g){
    color[v] = 1;
    for(auto to : g[v]){
        if(color[to]==0){
            if(cycle(to,color,g)) return true;
        }
        else if (color[to]==1){
            return true;
        }
    }
    color[v] = 2;
    return false;
}

void dfs(int v, vector<bool>& used, vector<vector<int>>& g, vector<ll>& dp){
    used[v]=true;
    for(auto to: g[v]){
        if(!used[to]){
            dfs(to,used,g,dp);
        }
        dp[v] = max(dp[v], 1+dp[to]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    ll n,m,k;
    cin >> n >> m >> k;
    vector<ll> a(n+1);
    for(int i =1;i<=n;i++) cin >> a[i];
    vector<vector<int>> g_main(n+1);
    for(int i =0;i<m;i++){
        int u,v;
        cin >> u >> v;
        g_main[u].push_back(v);
    }
    if(k==1){
        ll mn = 1e9+7;
        for(int i =1;i<=n;i++)mn=min(mn,a[i]);
        cout << mn << endl;
        return 0;
    }
    ll l=1, r=1e9+7;
    ll ans = r;
    while(l<=r){
        ll m = (l+r)/2;
        vector<vector<int>> g(n+1);
        vector<int> color(n+1,0);
        for(int i =1;i<=n;i++){
            if(a[i]<=m){
                for(auto to : g_main[i]){
                    if(a[to]<=m){
                        g[i].push_back(to);
                    }
                }
            }
        }  
        bool cyc = false; 
        for(int i=1;i<=n;i++){
            if(cycle(i,color, g)){
                cyc=true;
                break;
            }
        }
        if(cyc){
            ans = m;
            r = m-1;
        }
        else{
            vector<ll> dp(n+1,0);
            vector<bool> used(n+1,false);
            ll mx = 0;
            for(int i =1;i<=n;i++){
                if(!used[i]) dfs(i,used,g,dp);
            }
            for(int i =1;i<=n;i++) mx=max(mx,dp[i]);
            if(mx>=k-1){
                ans = m;
                r=m-1;
            }
            else{
                l=m+1;
            }
        }
    }
    if(ans==1e9+7) cout << -1 << endl;
    else cout << ans << endl;
}   
