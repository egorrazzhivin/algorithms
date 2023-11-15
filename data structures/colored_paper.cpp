/*
  nice heap + scanline problem
  link: https://acm.timus.ru/problem.aspx?space=1&num=1147&locale=ru
*/

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <tuple>
#include <map>
#include <queue>

int height, width, size;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> width >> height >> size;
    std::vector<int> colors(2505, 0);
    colors[1] = width * height;
    std::vector<bool> visited(10050, false);
    std::vector<int> points;
    std::vector<std::vector<int>> elements(size, std::vector<int>(5));
    for (int index = 0; index < size; ++index) {
        std::vector<int> lol(5);
        std::cin >> lol[0] >> lol[1] >> lol[2] >> lol[3] >> lol[4];
        if (!visited[lol[1]]) {
            visited[lol[1]] = true;
            points.emplace_back(lol[1]);
        }
        if (!visited[lol[3]]) {
            visited[lol[3]] = true;
            points.emplace_back(lol[3]);
        }
        elements[index] = lol;
    }
    if (!visited[height]) {
        points.emplace_back(height);
    }
    std::sort(points.begin(), points.end());
    std::map<int, int> level;
    for (int index = 0; index < static_cast<int>(points.size()); ++index) {
        int current_value = points[index];
        if (current_value == height) {
            break;
        }
        int next = points[index + 1];
        std::vector<std::vector<int>> dynamic;
        int local_width = next - current_value;
        for (int index = 0; index < size; ++index) {
            if (elements[index][1] <= current_value && elements[index][3] > current_value) {
                auto it = elements[index];
                std::vector<int> kek = {it[0], index, it[4], -1};
                std::vector<int> pip = {it[2], index, it[4], 1};
                dynamic.emplace_back(kek);
                dynamic.emplace_back(pip);
            }
        }
        std::sort(dynamic.begin(), dynamic.end());
        std::vector<bool> to_delete(2505, false);
        std::priority_queue<std::pair<int, int>> pq;
        int pointer = 0;
        int sz = static_cast<int>(dynamic.size());
        while (pointer < sz) {
            int y_coord = dynamic[pointer][0];
            if (y_coord == width) {
                break;
            }
            while (pointer < sz && dynamic[pointer][0] == y_coord) {
                int type = dynamic[pointer][3];
                int index = dynamic[pointer][1];
                int color = dynamic[pointer][2];
                if (type == 1) {
                    to_delete[index] = true;
                } else {
                    pq.push(std::make_pair(index, color));
                }
                ++pointer;
            }
            --pointer;
            while(!pq.empty() && to_delete[pq.top().first]) {
                pq.pop();
            }
            if (!pq.empty()) {
                int max_color = pq.top().second;
                int next_y = (pointer + 1 == sz ? width : dynamic[pointer + 1][0]);
                if (max_color > 1) {
                    colors[max_color] += local_width * (next_y - y_coord);
                }
            }
            ++pointer;
        }
    }
    int sum = 0;
    for (int color = 2; color <= 2500; ++color) {
        sum += colors[color];
    }
    colors[1] -= sum;
    for (int color = 1; color <= 2500; ++color) {
        int value = colors[color];
        if (value > 0) {
            std::cout << color << " " << value << '\n';
        }
    }
}
