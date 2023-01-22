#include <iostream>
#include<math.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <iterator>
typedef long long ll;
using namespace std;
//ios::sync_with_stdio(false);
const int INF = 1e9;

//O(m+n**2)

vector<vector<pair<int, int>>> g(1000);

int main() {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({ v,w });
		g[v].push_back({ u,w });
	}
	vector<int> dist(n + 1, INF);
	vector<bool> used(n + 1, false);
	vector<int> prev(n + 1, -1);
	int start;
	cin >> start;
	//start vertex
	int u = start;
	dist[start] = 0;
	while (u != -1) {
		used[u] = 1;
		for (auto p : g[u]) {
			if (dist[u] + p.second < dist[p.first]) {
				dist[p.first] = dist[u] + p.second;
				prev[p.first] = u;
			}
		}
		u = -1;
		int min_dist = INF;
		// choose next vertex
		for (int i = 1; i <= n; i++) {
			if (!used[i] && dist[i] < min_dist) {
				u = i;
				min_dist = dist[i];
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << "dist " << i << " = " << dist[i] << endl;
	}
}
