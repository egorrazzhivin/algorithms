#include <iostream>

using namespace std;

const int MAXN = 1e5;
int n, t[4 * MAXN];

//segment tree for finding sums on segments
//update O(logN)
//build O(N)
//get_sum O(logN)

void build(int a[], int v, int tl, int tr) {
	/*
	a - array
	v - number of vertex (root v has children with indexes 2*v and 2*v+1
	tl, tr - left and right boundaries of current segment
	*/
	if (tl == tr) {
		t[v] = a[tl]; //value of segment of length == 1 equals a[tl]==a[tr]
	}
	else {
		int tm = (tr + tl) >> 1;
		build(a, 2 * v, tl, tm); //build left subtree
		build(a, 2 * v + 1, tm + 1, tr); // build right subtree
		t[v] = t[2 * v] + t[2 * v + 1]; //sum in parent node = sub of its children
	}
}

int get_sum(int v, int tl, int tr, int l, int r) {
	/*
	l, r - left and right boundaries of current query
	*/
	if (l > r) {
		return 0;
	}
	if (l == tl && r == tr) {
		return t[v];
	}
	int tm = (tl + tr) >> 1;
	return get_sum(v * 2, tl, tm, l, min(r, tm))
		 + get_sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update(int v, int tl, int tr, int pos, int new_val) {
	/*
	pos, new_val - position and new value of element
	*/
	if (tl == tr) {
		t[v] = new_val;
	}
	else {
		int tm = (tl + tr) >> 1;
		if (pos <= tm) {
			update(v * 2, tl, tm, pos, new_val);
		}
		else {
			update(v * 2 + 1, tm + 1, tr, pos, new_val);
		}
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}

int main() {
	int a[100];
	int n = 100;
	int v = 1;
	int tl = 0, tr = n - 1;
	build(a, v, tl, tr);
}
