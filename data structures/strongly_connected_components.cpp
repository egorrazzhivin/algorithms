/*
https://www.spoj.com/problems/CAPCITY/
Kosaraju's algorithm

PPS: if answer is 0 we should iterate over all edges that connects different SCC
and calculate their degrees. If there are > 1 SCC such that out_degree = 0 answer is 0.
*/

#include <iostream>
#include<math.h>
#include <vector>
#include <algorithm>

typedef long long ll;
using namespace std;

void dfs1(int v, vector<vector<int>>& g, vector<int>& order, vector<bool>& used){
    used[v] = true;
    for(auto to : g[v]){
        if(!used[to]){
            dfs1(to, g, order, used);
        }
    }
    order.push_back(v);
}

void dfs2(int v, vector<vector<int>>& g_transposed, vector<int>& tmp, vector<bool>& used){
    used[v] = true;
    tmp.push_back(v);
    for(auto to : g_transposed[v]){
        if(!used[to]) {
            dfs2(to, g_transposed, tmp, used);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n+1), g_transposed(n+1);
    for(int i = 0;i<m;i++){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g_transposed[v].push_back(u);
    }
    vector<int> order;
    vector<bool> used1(n+1, false), used2(n+1, false);
    for(int i = 1;i<=n;i++){
        if(!used1[i]) dfs1(i, g, order, used1);
    }
    reverse(order.begin(), order.end());
    vector<vector<int>> components;
    for(int i = 0;i<n;i++){
        int v = order[i];
        if(!used2[v]){
            vector<int> tmp;
            dfs2(v, g_transposed, tmp, used2);
            components.push_back(tmp);
        }
    }
    vector<int> ans = components.back();
    sort(ans.begin(), ans.end());
    cout << (int)ans.size() << endl;
    for(auto to : ans) cout << to << " ";
    cout << endl;
} 
