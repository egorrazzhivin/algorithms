/*
link: https://cses.fi/problemset/task/1680/
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
 
const ll mod = 1e9+7;
const ll inf = 1e18;

vector<vector<int>> g(100100);
vector<int> dp(100100,-mod), p(100100,-1);

void dfs(int v, int par){
    for(auto to : g[v]){
        if(to!=par){
            if(dp[to]==-mod) dfs(to,v);
            if(dp[to]+1>dp[v]){
                dp[v] = dp[to]+1;
                p[v] = to;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for(int i =0;i<m;i++){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    dp[n] = 0;
    dfs(1,0);
    vector<int> ans;
    int cur = 1;
    bool was_n = false;
    while(cur!=-1){
        ans.push_back(cur);
        if(cur==n) was_n=true;
        cur=p[cur];
    }
    if(!was_n){
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    cout << ans.size() << endl;
    for(auto x : ans ) cout << x << " ";
    cout << endl;
}   
