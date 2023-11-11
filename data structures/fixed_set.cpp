// my implementation of unordered_set

#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <optional>

using std::optional;
using std::pair;
using std::vector;

const int64_t kPrime = 1e9 + 7;
const int64_t kAlpha = 10;

namespace generator {
    std::mt19937 generator(2007);
}

pair<int64_t, int64_t> GetCoef(int64_t prime) {
    static std::random_device device;
    static std::mt19937 generator(device());
    std::uniform_int_distribution<int64_t> dist_a(1, prime - 1);
    std::uniform_int_distribution<int64_t> dist_b(0, prime - 1);
    int64_t a = dist_a(generator);
    int64_t b = dist_b(generator);
    // std::cout << "a = " << a << " b = " << b << std::endl;

    return std::make_pair(a, b);
}

int64_t GetHash(int64_t a, int64_t b, int value, int64_t p, size_t len) {
    int64_t hash = ((a * static_cast<int64_t>(value) + b) % p) % len;
    return hash;
}

class FixedSet {
public:
    vector<vector<optional<int>>> Partition(const vector<int>& numbers) {
        vector<vector<optional<int>>> result = vector<vector<optional<int>>>(numbers.size());
        GenerateCoefs();
        for (auto elem : numbers) {
            auto value = GetHash(a_, b_, elem, kPrime, numbers.size());
            // std::cout << "elem = " << elem << " value = " << value << std::endl;
            result[value].emplace_back(elem);
        }

        return result;
    }

    void GenerateCoefs() {
        pair<int64_t, int64_t> coefs = GetCoef(kPrime);
        a_ = coefs.first;
        b_ = coefs.second;
    }

    void Initialize(const vector<int>& numbers) {
        if (!hash_table_.empty()) {
            hash_table_.clear();
            hashes_.clear();
        }
        if (numbers.empty()) {
            return;
        }
        int64_t length;
        do {
            length = 0;
            hash_table_ = Partition(numbers);
            for (auto elem : hash_table_) {
                length += elem.size() * elem.size();
            }
        } while (length > kAlpha * static_cast<int64_t>(numbers.size()));

        hashes_ = vector<pair<int64_t, int64_t>>(numbers.size(), std::make_pair(-1, -1));

        for (size_t index = 0; index < numbers.size(); ++index) {
            if (hash_table_[index].empty()) {
                continue;
            }
            vector<optional<int>> have = hash_table_[index];
            bool perfect = false;
            while (!perfect) {
                size_t current_size = hash_table_[index].size() * hash_table_[index].size();
                vector<optional<int>> second_level(current_size, std::nullopt);
                auto coefs = GetCoef(kPrime);
                int64_t current_a = coefs.first;
                int64_t current_b = coefs.second;
                bool can_make_perfect = true;
                for (auto element : have) {
                    // std::cout << "element = " << element.value() << '\n';
                    auto value = GetHash(current_a, current_b, element.value(),
                                         kPrime, current_size);
                    if (second_level[value] != std::nullopt) {
                        can_make_perfect = false;
                        break;
                    } else {
                        second_level[value] = element;
                    }
                }
                if (can_make_perfect) {
                    perfect = true;
                }
                if (perfect) {
                    hashes_[index] = std::make_pair(current_a, current_b);
                    hash_table_[index] = second_level;
                }
            }
            // std::cout << "fine " << '\n';
        }
    }

    bool Contains(int number) const {
        // std::cout << "number = " << number << '\n';
        if (hash_table_.empty()) {
            return false;
        }
        auto level_one = GetHash(a_, b_, number, kPrime, hash_table_.size());
        int64_t current_a = hashes_[level_one].first;
        int64_t current_b = hashes_[level_one].second;
        // std::cout << "level_one = " << level_one << " a = " << current_a;
        if (current_a == -1) {
            return false;
        }
        auto level_two = GetHash(current_a, current_b, number, kPrime,
                                 hash_table_[level_one].size());
        if (hash_table_[level_one][level_two] == number) {
            return true;
        } else {
            return false;
        }
    }

private:
    vector<vector<optional<int>>> hash_table_;
    int64_t a_, b_;
    vector<pair<int64_t, int64_t>> hashes_;
};
