/*
nice problem on binari lifting
link: https://codeforces.com/problemset/problem/1774/E?locale=en
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


int lift[200200][20];
vector<vector<int>> g(200200);
set<int> a,b;
vector<int> dp_a(200200,0), dp_b(200200,0);

int dfs(int v, int par, vector<int>& dp, set<int>& st){
    int cur = 0;
    for(auto to : g[v]){
        if(to!=par){
            int child = dfs(to, v, dp, st);
            //cout << "child = " << child << endl;
            dp[v]+=child;
            //cout << "v = " << v << " dp[v] = " << dp[v] << endl;
        }
    }
    if(dp[v]==0 && !st.count(v)) return 0;
    if(v!=1) dp[v]+=2;
    return dp[v];
}

void get_parent(int v, int par){
    lift[v][0] = par;
    for(auto to : g[v]){
        if(to!=par){
            get_parent(to, v);
        }
    }
}

int get_ancestor(int v, int dist){
    for(int bit = 0; bit<=18;bit++){
        if(dist&(1<<bit)){
            v = lift[v][bit];
        }
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,d;
    cin >> n >> d;
    for(int i =0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int m1,m2;
    cin >> m1;
    for(int i =0;i<m1;i++) {
        int x;
        cin >> x;
        a.insert(x);
    }
    cin >> m2;
    for(int i =0;i<m2;i++){
        int x;
        cin >> x;
        b.insert(x);
    }
    get_parent(1,1);
    for(int len = 1; len<=18; len++){
        for(int i =1;i<=n;i++){
            lift[i][len] = lift[lift[i][len-1]][len-1];
        }
    }  
    set<int> copy_b = b;
    for(auto x : a){
        b.insert(get_ancestor(x, d));
    }
    for(auto x : copy_b){
        a.insert(get_ancestor(x, d));
    }
    dfs(1,0,dp_a, a);
    dfs(1,0,dp_b, b);
    cout << dp_a[1] + dp_b[1] << endl;

}
