/*problem link: 
https://cses.fi/problemset/task/1653/
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
#include <algorithm>
#include <iterator>
#include <numeric>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for(int i =0;i<n;i++) cin >> w[i];
    vector<pair<int,int>> dp(1<<n);
    dp[0] = {1,0}; 
    //dp[mask] = {answer, weight of last ride};

    for(int mask = 1; mask<(1<<n); mask++){ //mask
        dp[mask] = {21,0}; //=inf
        for(int i=0;i<n;i++) { //person
            if(mask&(1<<i)){
                auto p = dp[mask^(1<<i)];
                int ans, weight;
                if(p.second+w[i]>x){
                    ans = p.first+1;
                    weight = w[i];
                }
                else{
                    ans = p.first;
                    weight = p.second+w[i];
                }
                dp[mask] = min(dp[mask], {ans, weight});

            }
        }
    }
    cout << dp[(1<<n)-1].first << endl;
}
