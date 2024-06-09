// please be patient i have autism

/*
  i'm not sure its hierholzers_algorithm but using this dfs we can somehow get euler path / cycle
  woah magic
  link: https://codeforces.com/contest/1981/problem/D
*/

#include <iostream>
#include<math.h>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <deque>
#include <memory>
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>
#include <thread>
#include <chrono>
#include <iomanip>  

using namespace std;

int get(int x) {
    if (x % 2) {
        return (x * (x - 1)) / 2 + x;
    } else {
        return (x * x) / 2 + 1;
    }
}

vector<int> primes;
vector<int> prime(300300, 1);

// i have NO IDEA why this is true but ok

void dfs(int v, vector<vector<int>>& g, vector<int>& result, set<pair<int, int>>& f) {
    while (!g[v].empty()) {
        int u = g[v].back();
        g[v].pop_back();
        if (f.count({u, v})) continue; // can use vector visited
        f.insert({u, v});
        f.insert({v, u});
        dfs(u, g, result, f);
    }
    result.push_back(primes[v]);
}



void sieve() {
    for (int i = 2; i <= 300000; i++) {
        if (prime[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= 300000; j += i) {
                prime[j] = 0;
            }
        }
    }
}

int main() {
    sieve();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int m = 1;
        while (get(m) < n - 1) {
            m++;
        }
        vector<vector<int>> g(m + 1);
        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= m; j++) {
                if ((m % 2 == 0) && i > 1 && j - i == 1 && (i % 2 == 0)) continue;
                g[i].push_back(j);
                if (i != j) g[j].push_back(i);
            }
        }
        vector<int> result;
        set<pair<int, int>> f;
        dfs(1, g, result, f);
        reverse(result.begin(), result.end());
        if (result.size() < n) cout << "HUI";
        for (int i = 0; i < n; i++) {
            // cout << primes[result[i]] << " ";
            cout << result[i] << " ";
        }
        cout << endl;
    }
}
