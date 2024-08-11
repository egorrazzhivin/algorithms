vector<int64_t> dp(n + 1, inf);
dp[1] = 0;
priority_queue<pair<int64_t, int64_t>, vector<pair<int64_t, int64_t>>,greater<pair<int64_t, int64_t>>> pq;
pq.push({0, 1});
while (!pq.empty()) {
    auto p = pq.top();
    pq.pop();
    int64_t v = p.second, distance = p.first;
    if (dp[v] != distance) continue;
    for (auto nxt : from[v]) {
	if (dp[v] + 1 < dp[nxt]) {
	    dp[nxt] = dp[v] + 1;
	    pq.push({dp[nxt], nxt});
	}
    }
}
