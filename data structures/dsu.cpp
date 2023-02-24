/* link: https://codeforces.com/contest/1559/problem/D1
given two forests. find maximum amount of 
edges that we can add in that forests so
they are still forests IF:
if we want to add edge (i,j) then we add
it in forest_1 AND forest_2
O(n^2logn)*/

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

struct dsu {
    int n;
    vector<int> p;
    dsu(int n){
        p.resize(n+1);
        for(int i =0;i<=n;i++)p[i]=i; // make set
    }
    int find(int a){ 
        //cout << "lol " << endl;
        return a==p[a] ? a : p[a] = find(p[a]); // find leader in set
    }
    void merge(int a, int b){
        a = find(a);
        b = find(b);
        if(a!=b) p[b]=a; // union of two sets
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int n,m1,m2;
    cin >> n >> m1 >> m2;
    dsu g1(n+1), g2(n+1);
    int h = 0;
    vector<pair<int,int>> ans;
    for(int i =0;i<m1;i++){
        int u,v;
        cin >> u >> v;
        g1.merge(u,v);
    }
    for(int i =0;i<m2;i++){
        int u,v;
        cin >> u >> v;
        g2.merge(u,v);
    }
    for(int i =1;i<=n;i++){
        for(int j = i+1; j<=n;j++){
            //we want to check if we can add edge (i,j);
            if(g1.find(i)!=g1.find(j) && g2.find(i)!=g2.find(j)){
                //cout << "here " << endl;
                h++;
                ans.push_back({i,j});
                g1.merge(i,j);
                g2.merge(i,j);
            }
        }
    }
    cout << h << endl;
    for(auto x : ans) cout << x.first << " " << x.second << endl;
}

