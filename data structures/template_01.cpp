// reminder: i have autism

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

const int64_t bound = 1e9 + 7;
const int64_t mod = 1e9 + 7;
const int64_t inf = 2e18;
 
int64_t gcd(int64_t a, int64_t b) {
    return b ? gcd(b, a % b) : a;
}
int64_t binexp(int64_t a, int64_t b) {
    if (!b) return 1;
    int64_t res = binexp(a, b / 2);
    res = (res * res) % mod;
    if (b % 2) res = (res * a) % mod;
    return res;
}
int64_t inv(int64_t x) {
    return binexp(x, mod - 2);
}
void print(string name, int64_t x) {
    cout << name << " = " << x << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}
