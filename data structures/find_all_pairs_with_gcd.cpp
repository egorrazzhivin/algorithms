// finding all pairs with gcd equal to x
// a[i] <= n;
// link: https://codeforces.com/contest/1884/problem/D?locale=en
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> cnt(n + 1, 0);
        vector<ll> dp(n + 1, 0); // dp[i] = cnt of pairs (x, y) such that gcd(x, y) = i
        for (int i = 0; i < n; i++) {
            ll x;
            cin >> x;
            cnt[x]++;
        }
        for (int i = n; i >= 1; i--) {
            ll total = 0;
            for (int j = i; j <= n; j += i) {
                total += cnt[j];
            }
            ll more = 0;
            for (int j = 2 * i; j <= n; j += i) {
                more += dp[j];
            }
            ll pairs = total * (total - 1) / 2;
            dp[i] = pairs - more;
        }
        ll ans = 0;
        vector<bool> bad(n + 1, false);
        for (int i = 1; i <= n; i++) {
            if (cnt[i]) {
                for (int j = i; j <= n; j += i) {
                    bad[j] = true;
                } 
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!bad[i]) ans += dp[i];
        }
        cout << ans << endl;
    }
}
