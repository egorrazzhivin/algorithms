/*
https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A
*/
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
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    s+='$';
    int n = (int)s.size();
    vector<int> p(n), c(n);
    {
        vector<pair<char,int>> a(n);
        for(int i =0;i<n;i++) a[i] = make_pair(s[i],i);
        sort(a.begin(),a.end());
        for(int i =0;i<n;i++) p[i] = a[i].second;
        c[p[0]]=0;
        for(int i =1;i<n;i++){
            if(a[i].first==a[i-1].first) c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]]+1;
        }
    }
    int k =0;
    while((1<<k) < n){
        vector<pair<pair<int,int>, int>> a(n);
        for(int i =0;i<n;i++){
            a[i] = make_pair(make_pair(c[i], c[(i+(1<<k))%n]), i);
        } 
        sort(a.begin(),a.end());
        for(int i =0;i<n;i++) p[i] = a[i].second;
        c[p[0]]=0;
        for(int i =1;i<n;i++){
            if(a[i].first==a[i-1].first) c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]]+1;
        }
        k++;
    }
    for(int i =0;i<n;i++) cout << p[i] << " " << s.substr(p[i], n-p[i]);
    cout << endl;
}
