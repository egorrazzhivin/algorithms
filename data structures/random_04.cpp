/*
link: https://codeforces.com/contest/1796/problem/D?locale=en
a bit weird dp imho
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

const ll inf = 1e18;

ll dp[200200][21][3];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        ll n,k,x;
        cin >> n >> k >> x;
        vector<ll> a(n);
        for(int i =0;i<n;i++) {
            cin >> a[i];
            a[i]-=x;
        }
        x*=2;
        for(int i =0;i<=n;i++){
            for(int j=0;j<=k;j++){
                for(int flag=0;flag<3;flag++) dp[i][j][flag] = -inf;
            }
        }
        dp[0][0][0] = 0;
        for(int i =0;i<n;i++){
            // i have visited
            for(int j =0;j<=k;j++){
                for(int flag=0;flag<2;flag++) dp[i][j][flag+1] = max(dp[i][j][flag+1], dp[i][j][flag]);
            }
            for(int j=0;j<=k;j++){
                for(int flag = 0;flag<3;flag++){
                    for(int add=0; add<=min(1,(int)(k-j));add++){
                        ll cur = dp[i][j][flag];
                        if(flag==1){ //inside 
                            cur += a[i]+add*x;
                        }
                        dp[i+1][add+j][flag] = max(dp[i+1][add+j][flag], cur);
                    }
                }
            }
        }
        cout << max(dp[n][k][1],dp[n][k][2]) << endl;
    }
}
