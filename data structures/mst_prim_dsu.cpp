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
typedef long long ll;
using namespace std;
 
const int mod = 1699997; //prime
const ll inf = 1e18;

struct dsu {
    int n;
    vector<int> sz,par;
 
    dsu(int n){
        for(int i =0;i<=n+1;i++){
            sz.push_back(1);
            par.push_back(i);
        }
    }
 
    int find(int a){
        return (a==par[a]) ? a : par[a] = find(par[a]);
    }
    
    void merge(int a, int b){
        a = find(a);
        b = find(b);
        if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        par[b]=a;
        sz[a]+=sz[b];
    }
 
};
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<pair<int, pair<int,int>>> a(m);
    for(int i =0;i<m;i++){
        cin >> a[i].second.first >> a[i].second.second >> a[i].first;
    }
    sort(a.begin(),a.end());
    dsu g(n);
    ll ans = 0;
    for(auto p : a){
        if(g.find(p.second.first)!=g.find(p.second.second)){
            g.merge(p.second.first, p.second.second);
            ans+=p.first;
        }
    }
    cout << ans << endl;
}
