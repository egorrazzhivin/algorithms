int t = 0;
void euler(int v, int p,vector<vector<int>>& g){
    t++;
    in[v] = t;
    for(auto to: g[v]){
        if(to!=p){
            euler(to,v,g);
        }
    }
    out[v] = t;
}
