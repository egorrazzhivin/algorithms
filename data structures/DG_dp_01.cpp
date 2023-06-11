/*
https://codeforces.com/contest/1573/problem/C?locale=en
interesting dp on dag
*/

bool cycle(int v, vector<vector<int>>&g, vector<bool>& used, vector<int>& color){
    color[v] = 1;
    for(auto to : g[v]){
        if(color[to]==0) {
            if(cycle(to, g,used,color)) return true;
        }
        else if(color[to]==1) return true;
    }
    color[v] = 2;
    return false;
}

void dfs(int v, vector<vector<int>>& g, vector<pair<int,int>>& d, vector<bool>& used){
    //cout << "cur v = " << v << endl;
    used[v]=true;
    for(auto to : g[v]){
        if(!used[to]) dfs(to,g,d,used);
        if(to<v) {
            d[v] = max(d[v], make_pair(d[to].first,to));
        }
        else{
            d[v] = max(d[v], make_pair(d[to].first+1,to));
        }
        //cout << "v = " << v << " to = " << to << " d[v].first = " << d[v].first << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> g(n+1);
        for(int i =1;i<=n;i++){
            int k;
            cin >> k;
            for(int j=0;j<k;j++){
                int x;
                cin >> x;
                g[i].push_back(x);
            }
        }
        vector<bool> used(n+1,false);
        vector<int> color(n+1,0);
        bool ok = true;
        for(int i =1;i<=n;i++){
            if(cycle(i,g,used,color)) ok = false;
        }
        if(!ok) {
            cout << -1 << endl;
            continue;
        }
        vector<pair<int,int>> d(n+1, make_pair(-1000100, -1));
        for(int i =1;i<=n;i++){
            if(g[i].empty()) d[i]=make_pair(1,i);
        }
        for(int i =1;i<=n;i++){
            if(!used[i]) dfs(i,g,d,used);
        }
        int ans =0;
        for(int i =1;i<=n;i++) ans=max(ans,d[i].first);
        cout << ans << endl;
    }   
}
