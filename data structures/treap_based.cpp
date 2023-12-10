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

namespace generator {
    std::mt19937 generator(132132);
}

std::uniform_int_distribution<int64_t> prior(0, 1e9);

std::unordered_map<int64_t, bool> priorities;

struct Node {
    int key;
    int size;
    int64_t priority;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int key, int64_t priority)
        : key(key),
          priority(priority),
          left(nullptr),
          right(nullptr) {
        size = 1;
    }
};

void get_size(std::shared_ptr<Node> root) {
    if (root == nullptr) {
        return 0;
    }
    return root->size;
}

void update_size(std::shared_ptr<Node> root) {
    if (root) {
        root->size = get_size(root->left) + get_size(root->right) + 1;
    }
    return;
}

void split(std::shared_ptr<Node> root, int key,
           std::shared_ptr<Node>& left, std::shared_ptr<Node>& right) {
    if (root == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (root->key < key) {
        split(root->right, key, root->right, right);
        left = root;
    } else {
        split(root->left, key, left, root->left);
        right = root;
    }
}

std::shared_ptr<Node> merge(std::shared_ptr<Node> left,
                            std::shared_ptr<Node> right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->priority < right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

// it was shared ptr
void insert(std::shared_ptr<Node>& root, std::shared_ptr<Node> it) {
    if (root == nullptr) {
        root = it;
        return;
    }
    if (it->priority < root->priority) {
        split(root, it->key, it->left, it->right);
        root = it;
    } else {
        if (it->key.first < root->key.first) {
            insert(root->left, it);
        } else {
            insert(root->right, it);
        }
    }
}

void erase(std::shared_ptr<Node>& root, int key) {
    if (root == nullptr) {
        return;
    }
    if (root->key == key) {
        root = merge(root->left, root->right);
        return;
    }
    if (root->key < key) {
        erase(root->right, key);
    } else {
        erase(root->left, key);
    }
}

bool find(std::shared_ptr<Node> root, int key) {
    if (root == nullptr) {
        return false;
    }
    if (root->key == key) {
        return true;
    }
    if (root->key < key) {
        return find(root->right, key);
    } else {
        return find(root->left, key);
    }
}

int main() {
  std::shared_ptr<Node> root = nullptr;
  std::unordered_map<int64_t, bool> priorities;
  int64_t value = prior(generator::generator);
  while (priorities[value]) {
      value = prior(generator::generator);
      priorities[value] = true;
  }
  auto it = std::make_shared<Node>(Node(key, value));
  insert(root, it);
  // ans so on
