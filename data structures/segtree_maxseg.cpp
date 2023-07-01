/*
  https://cses.fi/problemset/task/1188/
*/
struct node{
    ll seg, pref, suff, len;
};

node one = {1,1,1,1};
node zero = {0,0,0,1};

struct segtree{
    int n,sz;
    vector<node> tree;

    segtree(int n){
        sz=1;
        while(sz<n)sz*=2;
        tree.assign(2*sz-1, zero);
    }

    node combine(node a, node b){
        node c = a;
        c.len = a.len+b.len;
        c.seg = max(max(a.seg, b.seg), a.suff+b.pref);
        c.pref = (a.pref==a.len ? a.pref+b.pref : a.pref);
        c.suff = (b.suff==b.len ? a.suff+b.suff : b.suff);
        return c;
    }

    void init(vector<node>& a, int x,int lx, int rx){
        if(rx-lx==1) {
            if(lx<a.size()) tree[x]=a[lx];
        }
        else{
            int m = (lx+rx)>>1;
            init(a,2*x+1,lx,m);
            init(a,2*x+2,m,rx);
            tree[x] = combine(tree[2*x+1],tree[2*x+2]);
        }
    }

    void build(vector<node>& a){
        init(a,0,0,sz);
    }

    void update(int i, node v, int x, int lx, int rx){
        if(rx-lx==1) {
            tree[x] = v;
            return;
        }
        int m = (lx+rx)>>1;
        if(i<m) update(i, v, 2*x+1, lx,m);
        else update(i,v,2*x+2,m,rx);
        tree[x] = combine(tree[2*x+1],tree[2*x+2]);
    }

    void set(int i, node v){
        update(i,v,0,0,sz);
    }

    node get_sum(int l, int r, int x, int lx, int rx){
        if(rx<=l || r<= lx) return {0,0,0,0};
        if(lx>=l && rx<=r) return tree[x];
        int m = (lx+rx)>>1;
        node s1 = get_sum(l,r,2*x+1,lx,m);
        node s2 = get_sum(l,r,2*x+2,m,rx);
        return combine(s1,s2);
    }

    node sum(int l, int r){
        return get_sum(l,r,0,0,sz);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string s;
    cin >> s;
    n = (int)s.length();
    int m;
    cin >> m;
    vector<node> a_ones(n), a_zeros(n);
    for(int i =0;i<n;i++){
        if(s[i]=='0'){
            a_ones[i] = zero;
            a_zeros[i] = one;
        }
        else{
            a_ones[i] = one;
            a_zeros[i] = zero;
        }
    }
    segtree st_one(n), st_zero(n);
    st_one.build(a_ones);
    st_zero.build(a_zeros);
    while(m--){
        int x;
        cin >> x;
        x--;
        if(s[x]=='0'){
            st_one.set(x, one);
            st_zero.set(x, zero);
            s[x] = '1';
        }
        else{
            st_one.set(x, zero);
            st_zero.set(x, one);
            s[x] = '0';
        }
        //cout << "zeros = " << st_zero.sum(0,n).seg << " ones = " << st_one.sum(0,n).seg << endl;
        cout << max(st_zero.sum(0,n).seg, st_one.sum(0,n).seg) << " ";
    }
}
