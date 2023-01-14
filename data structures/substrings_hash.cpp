#include <iostream>
#include<math.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <iterator>
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
int p = 31;
ll powers[100];
ll hsh1[100],hsh2[100];

//rabin-karp algorithm
//O(s.length()+t.length());

int main() {
	string s, t;
	cin >> s >> t;
	powers[0] = 1;
	for (int i = 1; i < 100; i++) {
		powers[i] = (powers[i - 1] * p) % mod;
	}
	hsh1[0] = hsh2[0] = 0; //hash (empty str)
	//hsh[i] = (hsh[i-1]*p + s[i])%mod;
	for (int i = 1; i <= s.length(); i++) {
		hsh1[i] = (hsh1[i - 1] * p + (int)s[i - 1]) % mod;
	}
	for (int i = 1; i <= t.length(); i++) {
		hsh2[i] = (hsh2[i - 1] * p + (int)t[i - 1]) % mod;
	}
	//we compare hsh1[i:i+t.length()-1] with hsh2[t.length()]
	vector<int> ans; // for indices
	for (int i = t.length(); i <= s.length(); i++) {
		if ((((hsh1[i] - hsh1[i - t.length()] * powers[t.length()]) % mod + mod)%mod) == hsh2[t.length()]) {
			ans.push_back(i-t.length()+1);
		}
	}
	cout << "number of substrings = " << ans.size() << endl;
	cout << "indices: ";
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}
}
