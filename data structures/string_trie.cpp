/*
https://codeforces.com/contest/455/problem/B?locale=en
nice string-trie dp problem
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
 
typedef long long ll;
using namespace std;

struct string_trie{
    struct node{
        int cnt;
        vector<int> a;
        node() {
            cnt = 0;
            a.resize(26);
            for(int i = 0;i<26;i++) a[i] = -1;
        }
    };
    int n, vertex;
    vector<node> trie;
    string_trie(int n){
        trie.resize(n);
        vertex = 1;
    }
    void insert(string& s){
        int cur = 0;
        int k = (int)s.length();
        for(int i = 0;i<k;i++){
            int symbol = (int)(s[i]-'a');
            if(trie[cur].a[symbol] == -1){
                trie[cur].a[symbol] = vertex;
                vertex++;
            }
            trie[trie[cur].a[symbol]].cnt++;
            cur = trie[cur].a[symbol];
        }
    }
    bool dfs(int v, int par){
        for(int i = 0;i<26;i++){
            if(trie[v].a[i]==-1) continue;
            else {
                bool tmp = dfs(trie[v].a[i], v);
                //cout << "v = " << v << " symbol = " << i << " tmp = " << tmp << endl;
                if(tmp == false) return true;
            }
        }
        return false;
    }

    bool dfs_lose(int v){
        bool free = true;
        for(int i = 0;i<26;i++){
            if(trie[v].a[i]==-1) continue;
            else {
                free = false;
                bool tmp = dfs_lose(trie[v].a[i]);
                if(tmp == false) return true;
            }
        }
        if(free) return true;
        else return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n,k;
    cin >> n >> k;
    string_trie trie(100100);
    for(int i = 0;i<n;i++){
        string s;
        cin >> s;
        trie.insert(s);
    }
    bool ok = trie.dfs(0, -1);
    if(!ok) cout << "Second" << endl;
    else{
        bool ok2 = trie.dfs_lose(0);
        if(ok2) cout << "First" << endl;
        else{
            if(k%2==0) cout << "Second" << endl;
            else cout << "First" << endl;
        }
    }
}
