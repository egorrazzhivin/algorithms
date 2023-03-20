/* link: https://atcoder.jp/contests/abc294/tasks/abc294_e
tldr: given a 2*n (n up to 1e12)
and vector of compressed pairs(number, amount of adjacent numbers)
find all columns such that A1j=A2j */

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
typedef long long ll;
using namespace std;

const int mod = 1e9+7;
const ll inf = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll l,n1,n2;
    cin >> l >> n1 >> n2;
    vector<pair<ll,ll>> first(n1),second(n2);
    set<ll> unique;

    for(int i =0;i<n1;i++){
        cin >> first[i].first >> first[i].second;
        unique.insert(first[i].second);
    }
    for(int i =0;i<n2;i++){
        cin >> second[i].first >> second[i].second;
        unique.insert(second[i].first);
    }
    map<ll, pair<vector<pair<ll,ll>>,vector<pair<ll,ll>>>> lol;
    ll bound=1;
    for(int i =0;i<n1;i++){
        lol[first[i].first].first.push_back(make_pair(bound, bound+first[i].second-1));
        bound+=first[i].second;
    }
    bound = 1;
    for(int i =0;i<n2;i++){
        lol[second[i].first].second.push_back(make_pair(bound,bound+second[i].second-1));
        bound+=second[i].second;
    }
    ll ans = 0;
    for(auto x : unique){
        vector<pair<ll,ll>> row1 = lol[x].first;
        vector<pair<ll,ll>> row2 = lol[x].second;
        ll size1 = row1.size(), size2=row2.size();
        ll l1 = 0, l2=0;
        while(l1<size1 && l2<size2){
            pair<ll,ll> p1 = row1[l1], p2 = row2[l2];
            if(p1.second < p2.first) l1++;
            else if (p1.first > p2.second) l2++;
            else{
                if(p1.second < p2.second){
                    ans += p1.second-max(p1.first,p2.first)+1;
                    l1++;
                }
                else if (p2.second < p1.second){
                    ans += p2.second - max(p1.first,p2.first)+1;
                    l2++;
                }
                else{
                    ans += p2.second - max(p1.first,p2.first)+1;
                    l1++;
                }
            }
        }
    }
    cout << ans << endl;
}
