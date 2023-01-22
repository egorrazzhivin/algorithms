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

//O((m+n)logn)

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
	set<pair<int, int>> lol; // save (dist[i], i)
	lol.insert({ 0,start });
	while (!lol.empty()) {
		int u = (*lol.begin()).second;
		lol.erase(lol.begin());
		for (auto p : g[u]) {
			if (dist[u] + p.second < dist[p.first]) {
				lol.erase({ dist[p.first], p.first });
				dist[p.first] = dist[u] + p.second;
				lol.insert({ dist[p.first], p.first });
				prev[p.first] = u;
			}
		}
		
	}
	for (int i = 1; i <= n; i++) {
		cout << "dist " << i << " = " << dist[i] << endl;
	}
}
