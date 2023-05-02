/*
nice problem:
https://codeforces.com/contest/1726/problem/D?locale=en
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

void dfs(int v, vector<bool>& used, string& ans, vector<vector<pair<int,int>>>& g){
    used[v] = true;
    //cout << "v = " << v << endl;
    for(auto [to, index] : g[v]){
        if(!used[to]){
            ans[index] = '1';
            dfs(to, used,ans, g);
        }
    }
}


void dfs2(int v, vector<bool>& used, set<int>& check, vector<vector<int>>& g, map<pair<int,int>,int>& lol){
    used[v] = true;
    for(auto to : g[v]){
        if(!used[to]){
            check.insert(lol[{v,to}]);
            dfs2(to,used,check,g,lol);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        map<pair<int,int>,int> lol;
        string ans = string(m, '0');
        vector<bool> used(n+1, false);
        //map<pair<int,int>, int> lol;
        vector<vector<pair<int,int>>> g(n+1);
        vector<pair<int,int>> inv(m);
        for(int i =0;i<m;i++){
            int u,v;
            cin >> u >> v;
            g[u].push_back(make_pair(v,i));
            g[v].push_back(make_pair(u,i));
            inv[i]=make_pair(u,v);
            lol[{u,v}]=i;
            lol[{v,u}]=i;
        }
        dfs(1,used,ans,g);
        map<int,int> cnt;
        set<int> unique;
        multiset<int> uni;
        for(int i =0;i<m;i++){
            if(ans[i]=='0'){
                cnt[inv[i].first]++;
                cnt[inv[i].second]++;
                unique.insert(inv[i].first);
                unique.insert(inv[i].second);
            }
        }
        int calc = 0;
        string s = ans;
        
        if(unique.size()==3){
            bool ok = true;
            for(auto x : unique){
                if(cnt[x]!=2) ok = false;
            }
            if(ok) {
                            //bruteforce;
                vector<int> problems;
                for(int i =0;i<m;i++){
                    if(ans[i]=='0') problems.push_back(i);
                }
                ans[problems[0]]='1';
                vector<vector<int>> g_red(n+1);
                for(int i =0;i<m;i++){
                    if(i!=problems[1] && i!= problems[2]){
                        auto p = inv[i];
                        g_red[p.first].push_back(p.second);
                        g_red[p.second].push_back(p.first);
                    }
                }
                vector<bool> used_red(n+1, false);
                used_red[inv[problems[0]].first]=true;
                //string sss = string(m, '0');
                set<int> check;
                check.insert(problems[0]);
                dfs2(inv[problems[0]].second, used_red, check, g_red, lol);
                dfs2(inv[problems[0]].first, used_red,check, g_red,lol);
                for(int i =0;i<m;i++){
                    if(i!=problems[1] && i!=problems[2]){
                        if(!check.count(i)){
                            ans[i]='0';
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
}
