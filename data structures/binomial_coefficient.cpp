const int N = 1000;
ll C[N + 10][N + 10];
C[0][0] = 1;
for (ll i = 1; i <= N; i++) {
    C[i][1] = i;
    C[i][i] = C[i][0] = 1;
}
for (ll n = 2; n <= N; n++) {
    for (ll k = 2; k <= n; k++) {
        C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
        C[n][k] %= mod;
    }
}
