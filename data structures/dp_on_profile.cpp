/* tilings problem
https://cses.fi/problemset/task/2181/
O(m*(2^n))
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

const int mod = 1e9+7;
const ll inf = 1e18;


ll dp[1001][11][1025];
int main() {
    ios_base::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    for(int i =0;i<=m;i++){
        for(int j=0;j<=n;j++){
            for(int mask = 0; mask<=1024; mask++) dp[i][j][mask]=0;
        }
    }
    dp[0][n][0]=1;

    for(int i=1;i<=m;i++){
        for(int mask=0;mask<(1<<n); mask++) dp[i][0][mask] = dp[i-1][n][mask];

        for(int j=1; j<=n;j++){
            for(int mask = 0;mask<(1<<n);mask++){
                if(mask&(1<<(j-1))){ // if current square is available
                    dp[i][j][mask] += dp[i][j-1][mask^(1<<(j-1))];
                }
                else{
                    dp[i][j][mask] += dp[i][j-1][mask^(1<<(j-1))];
                    if(j>1 && (mask&(1<<(j-2)))==0){
                        dp[i][j][mask] += dp[i][j-2][mask];
                    }
                }
                dp[i][j][mask]%=mod;
            }
        }
    }
    cout << dp[m][n][0] << endl;
}
