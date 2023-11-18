void build(int node, int l, int r, vector<int>& a, vector<vector<int>>& seg){
    //if range length is 1 there's only one element to add and no children
    if (l == r){
        seg[node].push_back(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid, a, seg);
    build(node * 2 + 1, mid+1, r, a, seg);
    int i = 0,j = 0;
    // use two pointers to merge the two vectors in O(r-l+1)
    while (i < seg[node * 2].size() && j < seg[node * 2 + 1].size()){
        if (seg[node * 2][i]<seg[node * 2 + 1][j]) seg[node].push_back(seg[node * 2][i++]);
        else seg[node].push_back(seg[node * 2 + 1][j++]);
    }
    while (i<seg[node * 2].size()) seg[node].push_back(seg[node * 2][i++]);
    while (j<seg[node * 2 + 1].size()) seg[node].push_back(seg[node * 2+1][j++]);
    return;
}
//query
int query(int node,int l,int r,int lx,int rx,int x, vector<vector<int>>& seg){
    //if outside -> 0
    if (l>rx || r<lx) return 0;
    //if inside do binary search
    if (l>=lx && r<=rx){
        int L=0,R=seg[node].size()-1,mid,ans=0;
        while (L<=R){
            mid=(L+R)/2;
            if (seg[node][mid]<x){
                ans=mid+1;
                L=mid+1;
            }else R=mid-1;
        }return ans;
    }
    int mid=(l+r)/2;
    return query(node*2,l,mid,lx,rx,x, seg) + query(node*2+1,mid+1,r,lx,rx,x, seg);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> a(n + 1);
    vector<vector<int>> seg(4 * n + 5);
    build(1, 1, n, a, seg);
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << query(1, 1, n, l, r, x, seg);
    }
}
