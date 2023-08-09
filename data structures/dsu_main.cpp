struct dsu {
    int n;
    vector<int> p, sz;
    dsu(int n){
        p.resize(n+1);
        sz.resize(n+1);
        for(int i =0;i<=n;i++) {
            p[i]=i; 
            sz[i] = 1;
        }
    }
    int find(int a){ 
        return a==p[a] ? a : p[a] = find(p[a]); 
    }
    int get_size(int a){
        return sz[a];
    }
    void merge(int a, int b){
        a = find(a);
        b = find(b);
        if(a!=b) {
            if(sz[a] < sz[b]) swap(a,b);
            p[b] = a;
            sz[a] += sz[b];
        }
    }
};
