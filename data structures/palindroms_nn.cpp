#include <iostream>
#include <cmath>
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

//O(N*N)

string s;
int a[100][100];
string build(int i, int j) {
	if (i == j) {
		return string(1, s[i]);
	}
	else if (i > j) return string(0);
	else if (s[i] == s[j]) return string(1, s[i]) + build(i + 1, j - 1) + string(1, s[j]);
	else if (a[i + 1][j] > a[i][j]) return build(i + 1, j);
	else return build(i, j - 1);
}

int main() {
	cin >> s;
	//vector<vector<int>> a(s.length() + 1, vector<int>(s.length()+1));
	for (int j = 0; j < s.length(); j++) {
		a[j][j] = 1;
		for (int i = j - 1; i >= 0; i--) {
			if (s[i] == s[j]) {
				a[i][j] = 2 + a[i + 1][j - 1];
			}
			else {
				a[i][j] = max(a[i][j - 1], a[i + 1][j]);
			}
		}
	}
	string ans;
	ans = build(0, s.length() - 1);
	cout << ans << endl;
}
