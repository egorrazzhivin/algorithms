// a[i] from 1 to n
// dp[x] - number of pairs (i, j) so that gcd(i, j) = x
// cnt[x] - frequency of x
// O(n * logn)
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
