/*https://codeforces.com/contest/1725/problem/M
find shortest path between two vertices 1 and p for all p
in directed graph*/

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

const int mod = 998244353;
const ll inf = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> G(n+n+5);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        G[u].push_back({v,w});
        G[v+n].push_back({u+n,w});
    }
    for(int i=1;i<=n;i++)
    {
        G[i].push_back({i+n,0});
    }
    vector<long long> dis(n+n+5,1e18);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    pq.push({0,1});
    dis[1]=0;
    while(!pq.empty())
    {
        auto p=pq.top();pq.pop();
        if(dis[p.second]!=p.first)continue;
        for(auto x:G[p.second])
        {
            if(dis[x.first]>dis[p.second]+x.second)
            {
                dis[x.first]=dis[p.second]+x.second;
                pq.push({dis[x.first],x.first});
            }
        }
    }
    for(int i=2;i<=n;i++)
    {
        cout<<((dis[i+n]==1e18?) -1 : dis[i+n])<<' ';
    }
}
