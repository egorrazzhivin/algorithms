vector<vector<int>> g(200200);
vector<int> d(200200, 0);
int bin_up[200200][20];

void dfs(int v, int par, int h) {
    bin_up[v][0] = par;
    d[v] = h;
    for (int sz = 1; sz <= 18; sz++) {
        bin_up[v][sz] = bin_up[bin_up[v][sz - 1]][sz - 1];
    }
    for (auto to : g[v]) {
        if (to != par) dfs(to, v, h + 1);
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);

    for (int sz = 18; sz >= 0; sz--) {
        if (d[u] - (1 << sz) >= d[v]) u = bin_up[u][sz];
    }

    for (int sz = 18; sz >= 0; sz--) {
        if (bin_up[u][sz] != bin_up[v][sz]) {
            u = bin_up[u][sz];
            v = bin_up[v][sz];
        }
    }

    return (u == v ? u : bin_up[u][0]);
}
