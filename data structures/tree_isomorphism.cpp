/*
  tree isomorphism in O(VlogV)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <functional>

const int64_t mod = 1e9 + 7;

int size;

std::vector<int> Centroid(std::vector<std::vector<int>>& Graph) {
    std::vector<int> centroid;
    std::vector<int> sz(size + 1);
    std::function<void(int, int)> work = [&](int ver, int prev) {
            sz[ver] = 1;
            bool is_centroid = true;
            for (auto to : Graph[ver]) {
                if (to != prev) {
                    work(to, ver);
                    sz[ver] += sz[to];
                    if (sz[to] > size / 2) {
                        is_centroid = false;
                    }
                }
            }
            if (size - sz[ver] > size / 2) {
                is_centroid = false;
            }
            if (is_centroid) {
                centroid.push_back(ver);
            }
    };
    work(1, -1);
    return centroid;
}

void hole(int cur_x, int parent_x, int cur_y, int parent_y,
             std::vector<std::vector<int>>& Graph_X,
             std::vector<std::vector<int>>& Graph_Y,
             std::vector<int64_t>& hash_x,
             std::vector<int64_t>& hash_y,
             std::vector<int>& answer) {
    answer[cur_y] = cur_x;
    std::vector<std::pair<int64_t, int>> child_x, child_y;
    for (auto to : Graph_X[cur_x]) {
        if (to != parent_x) {
            child_x.emplace_back(std::make_pair(hash_x[to], to));
        }
    }
    for (auto to : Graph_Y[cur_y]) {
        if (to != parent_y) {
            child_y.emplace_back(std::make_pair(hash_y[to], to));
        }
    }
    std::sort(child_x.begin(), child_x.end());
    std::sort(child_y.begin(), child_y.end());
    int child_size = child_y.size();
    for (int index = 0; index < child_size; ++index) {
        hole(child_x[index].second, cur_x, child_y[index].second, cur_y,
                    Graph_X, Graph_Y, hash_x, hash_y, answer);
    }
}

int64_t dfs(int cur, int parent, std::vector<std::vector<int>>& Graph,
            std::vector<int64_t>& hash) {
    int64_t result = 42;
    std::vector<int64_t> child;
    for (auto to : Graph[cur]) {
        if (to != parent) {
            child.emplace_back(dfs(to, cur, Graph, hash));
        }
    }
    for (auto value : child) {
        int64_t temporary = ((value * value) + 42) % mod;
        result += temporary;
        if (result > mod) {
            result -= mod;
        }
    }
    hash[cur] = result;
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> size;
    if (size == 1) {
        std::cout << 1 << '\n';
        return 0;
    }
    std::vector<std::vector<int>> Graph_X(size + 1);
    std::vector<std::vector<int>> Graph_Y(size + 1);
    std::vector<int64_t> hash_x(size + 1, 0);
    std::vector<int64_t> hash_y(size + 1, 0);
    for (int index = 0; index < size - 1; ++index) {
        int vertex_a, vertex_b;
        std::cin >> vertex_a >> vertex_b;
        Graph_Y[vertex_a].push_back(vertex_b);
        Graph_Y[vertex_b].push_back(vertex_a);
    }
    for (int index = 0; index < size - 1; ++index) {
        int vertex_a, vertex_b;
        std::cin >> vertex_a >> vertex_b;
        Graph_X[vertex_a].push_back(vertex_b);
        Graph_X[vertex_b].push_back(vertex_a);
    }
    std::vector<int> centers_x = Centroid(Graph_X);
    std::vector<int> centers_y = Centroid(Graph_Y);
    if (centers_x.size() != centers_y.size()) {
        std::cout << -1 << '\n';
        return 0;
    }
    int center_x = centers_x[0];
    int64_t value_x = dfs(center_x, -1, Graph_X, hash_x);
    for (auto center_y : centers_y) {
        int64_t value_y = dfs(center_y, -1, Graph_Y, hash_y);
        if (value_y == value_x) {
            std::vector<int> answer(size + 1, -1);
            hole(center_x, -1, center_y, -1, Graph_X, Graph_Y,
                 hash_x, hash_y, answer);
            for (int vertex = 1; vertex <= size; ++vertex) {
                std::cout << answer[vertex] << '\n';
            }
            return 0;
        }
    }
    std::cout << -1 << '\n';
}
