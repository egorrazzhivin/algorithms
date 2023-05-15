struct segtree{
    int n,sz;
    vector<ll> tree;

    segtree(int n){
        sz=1;
        while(sz<n)sz*=2;
        tree.assign(2*sz-1, 0);
    }

    void init(vector<int>& a, int x,int lx, int rx){
        if(rx-lx==1) {
            if(lx<a.size()) tree[x]=a[lx];
        }
        else{
            int m = (lx+rx)>>1;
            init(a,2*x+1,lx,m);
            init(a,2*x+2,m,rx);
            tree[x] = tree[2*x+1]+tree[2*x+2];
        }
    }

    void build(vector<int>& a){
        init(a,0,0,sz);
    }

    void update(int i, int v, int x, int lx, int rx){
        if(rx-lx==1) {
            tree[x] = v;
            return;
        }
        int m = (lx+rx)>>1;
        if(i<m) update(i, v, 2*x+1, lx,m);
        else update(i,v,2*x+2,m,rx);
        tree[x] = tree[2*x+1]+tree[2*x+2];
    }

    void set(int i, int v){
        update(i,v,0,0,sz);
    }

    ll get_sum(int l, int r, int x, int lx, int rx){
        if(rx<=l || r<= lx) return 0;
        if(lx>=l && rx<=r) return tree[x];
        int m = (lx+rx)>>1;
        ll s1 = get_sum(l,r,2*x+1,lx,m);
        ll s2 = get_sum(l,r,2*x+2,m,rx);
        return s1 + s2;
    }

    ll sum(int l, int r){
        return get_sum(l,r,0,0,sz);
    }

};
