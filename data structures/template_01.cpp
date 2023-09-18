// reminder: i have autism

#include <iostream>
#include<math.h>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <deque>
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>
#include <thread>
#include <chrono>
#include <iomanip>    
typedef long long ll;
using namespace std;

const ll mod = 1e9+7;
const ll inf = 2e18;
 
int bitcount(ll n) { return n == 0 ? 0 : bitcount(n & (n - 1)) + 1;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
ll binexp(ll a, ll b){
    if (!b) return 1;
    ll res = binexp(a, b/2);
    res = (res*res)%mod;
    if(b%2) res = (res*a)%mod;
    return res;
}
ll rev(ll x) {return binexp(x, mod - 2);}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}  
