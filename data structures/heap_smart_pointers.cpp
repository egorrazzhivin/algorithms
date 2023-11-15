/*
  heap with smart pointers
  link: https://www.problems.ru/view_problem_details_new.php?id=98676
*/

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <string>
#include <cassert>
#include <memory>

const int64_t MAXM = 100005;

using std::cout;

struct Segment {
    std::shared_ptr<Segment> prev;
    std::shared_ptr<Segment> next;
    int64_t left, right, index;
    bool free;

    Segment(std::shared_ptr<Segment> prev, std::shared_ptr<Segment> next,
            int64_t left, int64_t right, int64_t index, bool free)
        : prev(prev),
          next(next),
          left(left),
          right(right),
          index(index),
          free(free) {
    }
};

struct Heap {
    std::shared_ptr<Segment> heap[MAXM];
    int64_t size;

    explicit Heap(int64_t size) : size(size) {
    }

    bool better(int lhs, int rhs) {
        if (heap[lhs]->right - heap[lhs]->left > heap[rhs]->right - heap[rhs]->left) {
            return true;
        } else {
            return false;
        }
    }

    bool equal(int lhs, int rhs) {
        if (heap[lhs]->right - heap[lhs]->left == heap[rhs]->right - heap[rhs]->left) {
            return true;
        } else {
            return false;
        }
    }

    void heapify(int64_t index) {
        int64_t left_child = (index << 1) + 1;
        int64_t right_child = (index << 1) + 2;
        int64_t largest = index;
        if (left_child < size) {
            if (better(left_child, largest)) {
                largest = left_child;
            } else if (equal(left_child, largest)) {
                if (heap[left_child]->left < heap[largest]->left) {
                    largest = left_child;
                }
            }
        }
        if (right_child < size) {
            if (better(right_child, largest)) {
                largest = right_child;
            } else if (equal(right_child, largest)) {
                if (heap[right_child]->left < heap[largest]->left) {
                    largest = right_child;
                }
            }
        }
        if (largest != index) {
            swap(index, largest);
            heapify(largest);
        }
        return;
    }

    void swap(int64_t lhs, int64_t rhs) {
        auto mirror = heap[lhs];
        heap[lhs] = heap[rhs];
        heap[rhs] = mirror;
        heap[lhs]->index = lhs;
        heap[rhs]->index = rhs;
    }

    void extract_max() {
        --size;
        if (size > 0) {
            swap(0, size);
            heapify(0);
        }
    }

    bool compare(int parent, int child) {
        if (better(parent, child)) {
            return true;
        } else if (equal(parent, child)) {
            if (heap[parent]->left < heap[child]->left) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void sift_up(int64_t index) {
        int64_t parent = (index - 1) >> 1;
        while (index > 0 && !compare(parent, index)) {
            swap(parent, index);
            index = parent;
            if (index > 0) {
                parent = (index - 1) >> 1;
            }
        }
    }

    int64_t get_max_value() {
        return heap[0]->right - heap[0]->left + 1;
    }

    void erase(int64_t index) {
        swap(index, size - 1);
        --size;
        if (index >= size) {
            return;
        }
        sift_up(index);
        heapify(index);
    }

    void add(std::shared_ptr<Segment> other) {
        other->index = size;
        heap[size] = other;
        sift_up(size++);
    }

    int64_t get_size() {
        return size;
    }
};

std::shared_ptr<Segment> closed[MAXM];
int64_t type[MAXM];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int64_t length, queries;
    std::cin >> length >> queries;
    int64_t begin = 1;
    Heap Hp(begin);
    Hp.heap[0] = std::make_shared<Segment>(Segment(nullptr, nullptr, 1, length, 0, true));
    for (int64_t oper = 0; oper < queries; ++oper) {
        int64_t value;
        std::cin >> value;
        if (value > 0) {
            if (Hp.get_size() == 0) {
                std::cout << -1 << '\n';
                type[oper] = -1;
                continue;
            }
            int64_t mx = Hp.get_max_value();
            if (value > mx) {
                std::cout << -1 << '\n';
                type[oper] = -1;
                continue;
            }
            type[oper] = 0;
            std::shared_ptr<Segment> optimal = Hp.heap[0];
            int64_t left = optimal->left;
            std::cout << left << '\n';
            int64_t right = left + value - 1;
            optimal->left += value;
            if (optimal->left <= optimal->right) {
                closed[oper] = std::make_shared<Segment>(Segment(optimal->prev,
                                                        optimal, left, right, -1, false));
            } else {
                closed[oper] = std::make_shared<Segment>(Segment(optimal->prev,
                                                        optimal->next, left, right, -1, false));
                if (optimal->next != nullptr) {
                    assert(optimal->next);
                    optimal->next->prev = closed[oper];
                }
                if (optimal->prev != nullptr) {
                    assert(optimal->prev);
                    optimal->prev->next = closed[oper];
                }
            }
            if (optimal->left > optimal->right) {
                Hp.extract_max();
            } else {
                if (optimal->prev != nullptr) {
                    assert(optimal->prev);
                    optimal->prev->next = closed[oper];
                }
                optimal->prev = closed[oper];
                Hp.heapify(optimal->index);
            }
        } else {
            value *= -1;
            type[oper] = 0;
            if (type[value - 1] == -1) {
                continue;
            }
            
            std::shared_ptr<Segment> current = closed[value - 1];
            if (current == nullptr) {
                int getero = 2;
                while (getero != 1) {
                    if (getero == 2) {
                        ++getero;
                    } else {
                        --getero;
                    }
                }
            }
            std::shared_ptr<Segment> prev_cur = current->prev;
            std::shared_ptr<Segment> next_cur = current->next;
            bool pr = false, ne = false;
            if (prev_cur != nullptr) {
                assert(prev_cur);
                pr = prev_cur->free;
            }
            if (next_cur != nullptr) {
                assert(next_cur);
                ne = next_cur->free;
            }
            if (!pr && !ne) {
                current->free = true;
                Hp.add(current);
            } else if (!pr && ne) {
                next_cur->left = current->left;
                next_cur->prev = current->prev;
                if (current->prev != nullptr) {
                    assert(current->prev);
                    current->prev->next = next_cur;
                }
                Hp.sift_up(next_cur->index);
            } else if (!ne && pr) {
                prev_cur->right = current->right;
                prev_cur->next = current->next;
                if (current->next != nullptr) {
                    assert(current->next);
                    current->next->prev = prev_cur;
                }
                Hp.sift_up(prev_cur->index);
            } else {
                prev_cur->right = next_cur->right;
                prev_cur->next = next_cur->next;
                if (next_cur->next != nullptr) {
                    assert(next_cur->next);
                    next_cur->next->prev = prev_cur;
                }
                Hp.erase(next_cur->index);
                Hp.sift_up(prev_cur->index);
            }
        }
    }
}
