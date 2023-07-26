/*
want to leave it here because it looks like
based fun problem
https://codeforces.com/contest/1852/problem/A?locale=en
O(n+k), but O(n) is possible
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        vector<int> a(n+1,0);
        for(int i =1;i<=n;i++) cin >> a[i];
        ll ans = 1;
        ll step = 1;
        ll cur_pos = 2;
        if(a[1]>1){
            cout << 1 << endl;
            continue;
        }
        if(n==1){
            cout << k+1 << endl;
            continue;
        }
        for(int day = 1; day<=k; day++){
            ans+=step;
            if(ans>=a[cur_pos]){
                while(cur_pos<=n && ans>=a[cur_pos]){
                    step++;
                    ans++;
                    cur_pos++;
                }
            }
        }
        cout << ans << endl;
    }
}
