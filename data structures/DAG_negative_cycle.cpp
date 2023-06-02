/*
link: https://cses.fi/problemset/task/1197/
bellman-ford algorithm 
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

struct edge{
    ll a,b,w;
};

vector<edge> g(100100);
vector<ll> dp(100100,-inf), p(100100,-1);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for(int i =0;i<m;i++){
        cin >> g[i].a >> g[i].b >> g[i].w;
    }
    dp[1] = 0;
    int x = -1;
    for(int i =0;i<n;i++){
        x = -1;
        for(int j =0;j<m;j++){
            if(dp[g[j].a] + g[j].w < dp[g[j].b]){
                dp[g[j].b] = dp[g[j].a] + g[j].w;
                x = g[j].b;
                p[g[j].b] = g[j].a;
            }
        }
    }
    if(x==-1){
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    //now lets find vertex in cycle;
    for(int i =0;i<n;i++) x = p[x];
    int cur = x;
    vector<int> cycle;
    cycle.push_back(cur);
    cur = p[cur];
    while(cur!=x){
        cycle.push_back(cur);
        cur=p[cur];
    }
    cycle.push_back(x);
    reverse(cycle.begin(),cycle.end());
    for(auto x : cycle) cout << x << " ";
    cout << endl;
}   
