struct fenwick{
    vector<ll> f;

    fenwick(int n){
        f.assign(n,0);
    }

    void inc(int pos, ll val){
        for(int i = pos; i<(int)f.size(); i=(i|(i+1))){
            f[i] += val;
        }
    }

    ll get(int r){
        ll res = 0;
        for(int i =r; i>=0; i=(i&(i+1))-1){
            res+=f[i];
        }

        return res;
    }
};
