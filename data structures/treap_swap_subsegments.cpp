/*
swap subsegments in array using treap
link: https://codeforces.com/gym/102787/problem/A
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <tuple>
#include <memory>
#include <random>
#include <map>

namespace generator {
    std::mt19937 generator(12132);
}

struct Node {
    int key;
    int size;
    int64_t priority;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node() : left(nullptr), right(nullptr) {
        size = 0;
    }

    Node(int key, int64_t priority)
        : key(key),
          priority(priority),
          left(nullptr),
          right(nullptr) {
        size = 1;
    }
};

int get_size(std::shared_ptr<Node> root) {
    if (root == nullptr) {
        return 0;
    }
    return root->size;
}

void update_size(std::shared_ptr<Node> root) {
    if (root) {
        root->size = get_size(root->left) + get_size(root->right) + 1;
    }
}

void split(std::shared_ptr<Node> root, int key,
           std::shared_ptr<Node>& left, std::shared_ptr<Node>& right) {
    if (root == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    }
    if (get_size(root->left) >= key) {
        split(root->left, key, left, root->left);
        right = root;
    } else {
        split(root->right, key - get_size(root->left) - 1, root->right, right);
        left = root;
    }
    update_size(left);
    update_size(right);
}

void merge(std::shared_ptr<Node>& root, std::shared_ptr<Node> left,
                            std::shared_ptr<Node> right) {
    if (left == nullptr) {
        root = right;
        update_size(root);
        return;
    }
    if (right == nullptr) {
        root = left;
        update_size(root);
        return;
    }
    if (left->priority < right->priority) {
        merge(left->right, left->right, right);
        root = left;
    } else {
        merge(right->left, left, right->left);
        root = right;
    }
    update_size(root);
}

void insert(std::shared_ptr<Node>& root, std::shared_ptr<Node> it) {
    if (root == nullptr) {
        root = it;
        update_size(root);
        return;
    }
    if (it->priority < root->priority) {
        split(root, it->key, it->left, it->right);
        root = it;
        update_size(root);
    } else {
        if (it->key < root->key) {
            insert(root->left, it);
        } else {
            insert(root->right, it);
        }
    }
}

void traverse(std::vector<int>& result, std::shared_ptr<Node> root) {
    if (root == nullptr) {
        return;
    }
    traverse(result, root->left);
    result.emplace_back(root->key);
    traverse(result, root->right);
}


int main() {
    int n;
    std::cin >> n;
    static std::random_device device;
    static std::mt19937 generator(device());
    std::uniform_int_distribution<int64_t> prior(0, 1e15);
    std::vector<std::pair<int, int>> operations(n);
    std::shared_ptr<Node> root = nullptr;
    std::map<int64_t, bool> priorities;
    for (int index = 1; index <= n; ++index) {
        int a, b;
        std::cin >> a >> b;
        operations[index - 1] = std::make_pair(a, b);
        int64_t value = prior(generator);
        while (priorities[value]) {
          value = prior(generator);
          priorities[value] = true;
        }
        auto it = std::make_shared<Node>(Node(index, value));
        merge(root, root, it);
    }
    for (auto [left, right] : operations) {
        if (left >= right) continue;
        int to_end = n - right + 1;
        int to_right = right - left;
        int step = std::min(to_end, to_right);
        int left_begin = left, left_end = left + step - 1;
        int right_begin = right, right_end = right + step - 1;
        std::shared_ptr<Node> prefix = nullptr;
        std::shared_ptr<Node> rest = nullptr;
        split(root, left - 1, prefix, rest);
        std::shared_ptr<Node> left_part = nullptr;
        std::shared_ptr<Node> rest_two = nullptr;
        split(rest, step, left_part, rest_two);
        std::shared_ptr<Node> middle_part = nullptr;
        std::shared_ptr<Node> rest_two_mid = nullptr;
        split(rest_two, right - (left_end + 1), middle_part, rest_two_mid);
        std::shared_ptr<Node> right_part = nullptr;
        std::shared_ptr<Node> rest_three = nullptr;
        split(rest_two_mid, right_end - right_begin + 1, right_part, rest_three);
        merge(prefix, prefix, right_part);
        merge(prefix, prefix, middle_part);
        merge(prefix, prefix, left_part);
        merge(prefix, prefix, rest_three);
        root = prefix;
    }
    std::vector<int> result;
    for (int i = 1; i <= n; ++i) {
        std::shared_ptr<Node> res = nullptr;
        std::shared_ptr<Node> other = nullptr;
        split(root, 1, res, other);
        result.push_back(res->key);
        root = other;
    }
    for (auto x : result) {
        std::cout << x << " ";
    }
    std::cout << '\n';
}
