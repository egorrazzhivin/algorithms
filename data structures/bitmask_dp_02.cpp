/*
problem statement:
we have n <= 1000 playing cubes with k<=20 faces;
we throw n dice and then multiply values that we observe (call this number A)
what is the propability that A has an odd number of divisors?
-------
solve problem using dp
O(256*n*k) solution
idea: check parity of each prime number at each step
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

ll binexp(ll a, ll b){
    if (!b) return 1;
    ll res = binexp(a, b/2);
    res = (res*res)%mod;
    if(b%2) res = (res*a)%mod;
    return res;
}
ll rev(ll x) {return binexp(x, mod - 2);}

ll dp[1007][2][2][2][2][2][2][2][2];

int main() {
    ios_base::sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    for(int i =0;i<=n+1; i++){
        for(int j=0;j<2;j++){
            for(int m=0;m<2;m++){
                for(int l=0;l<2; l++){
                    for(int h = 0;h<2;h++){
                        for(int d=0; d<2; d++){
                            for(int g = 0; g<2;g++){
                                for(int c =0; c<2;c++){
                                    for(int b=0;b<2;b++){
                                        dp[i][j][m][l][h][d][g][c][b] = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(int f=1; f<=k;f++){
        if(f==1) dp[1][0][0][0][0][0][0][0][0]+=1;
        if(f==2) dp[1][1][0][0][0][0][0][0][0]+=1;
        if(f==3) dp[1][0][1][0][0][0][0][0][0]+=1;
        if(f==4) dp[1][0][0][0][0][0][0][0][0]+=1;
        if(f==5) dp[1][0][0][1][0][0][0][0][0]+=1;
        if(f==6) dp[1][1][1][0][0][0][0][0][0]+=1;
        if(f==7) dp[1][0][0][0][1][0][0][0][0]+=1;
        if(f==8) dp[1][1][0][0][0][0][0][0][0]+=1;
        if(f==9) dp[1][0][0][0][0][0][0][0][0]+=1;
        if(f==10) dp[1][1][0][1][0][0][0][0][0]+=1;
        if(f==11) dp[1][0][0][0][0][1][0][0][0]+=1;
        if(f==12) dp[1][0][1][0][0][0][0][0][0]+=1;
        if(f==13) dp[1][0][0][0][0][0][1][0][0]+=1;
        if(f==14) dp[1][1][0][0][1][0][0][0][0]+=1;
        if(f==15) dp[1][0][1][1][0][0][0][0][0]+=1;
        if(f==16) dp[1][0][0][0][0][0][0][0][0]+=1;
        if(f==17) dp[1][0][0][0][0][0][0][1][0]+=1;
        if(f==18) dp[1][1][0][0][0][0][0][0][0]+=1;
        if(f==19) dp[1][0][0][0][0][0][0][0][1]+=1;
        if(f==20) dp[1][0][0][1][0][0][0][0][0]+=1;
    }

    for(int i =2; i<=n;i++){
        for(int j=0;j<2;j++){
            for(int m=0;m<2;m++){
                for(int l=0;l<2; l++){
                    for(int h = 0;h<2;h++){
                        for(int d=0; d<2; d++){
                            for(int g = 0; g<2;g++){
                                for(int c =0; c<2;c++){
                                    for(int b=0;b<2;b++){
                                        for(int f=1; f<=k;f++){
                                            if(f==1) {
                                                dp[i][j][m][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d][g][c][b] %= mod;
                                            }
                                            if(f==2){
                                                dp[i][j^1][m][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j^1][m][l][h][d][g][c][b] %=mod;
                                            }
                                            if(f==3){
                                                dp[i][j][m^1][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m^1][l][h][d][g][c][b] %=mod;
                                            }
                                            if(f==4){
                                                dp[i][j][m][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d][g][c][b] %=mod;
                                            }
                                            if(f==5){
                                                dp[i][j][m][l^1][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l^1][h][d][g][c][b]%=mod;
                                            }
                                            if(f==6){
                                                dp[i][j^1][m^1][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j^1][m^1][l][h][d][g][c][b]%=mod;
                                            }
                                            if(f==7){
                                                dp[i][j][m][l][h^1][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h^1][d][g][c][b]%=mod;
                                            }
                                            if(f==8){
                                                dp[i][j^1][m][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j^1][m][l][h][d][g][c][b]%=mod;
                                            }
                                            if(f==9){
                                                dp[i][j][m][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d][g][c][b] %= mod;
                                            }
                                            if(f==10){
                                                dp[i][j^1][m][l^1][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j^1][m][l^1][h][d][g][c][b] %= mod;
                                            }
                                            if(f==11){
                                                dp[i][j][m][l][h][d^1][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d^1][g][c][b] %= mod;
                                            }
                                            if(f==12){
                                                dp[i][j][m^1][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m^1][l][h][d][g][c][b] %= mod;
                                            }
                                            if(f==13){
                                                dp[i][j][m][l][h][d][g^1][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d][g^1][c][b] %= mod;
                                            }   
                                            if(f==14){
                                                dp[i][j^1][m][l][h^1][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j^1][m][l][h^1][d][g][c][b] %= mod;
                                            }
                                            if(f==15){
                                                dp[i][j][m^1][l^1][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m^1][l^1][h][d][g][c][b] %= mod;
                                            }
                                            if(f==16){
                                                dp[i][j][m][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d][g][c][b] %= mod;
                                            }
                                            if(f==17){
                                                dp[i][j][m][l][h][d][g][c^1][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d][g][c^1][b] %= mod;
                                            }
                                            if(f==18){
                                                dp[i][j^1][m][l][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j^1][m][l][h][d][g][c][b] %= mod;
                                            }
                                            if(f==19){
                                                dp[i][j][m][l][h][d][g][c][b^1] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l][h][d][g][c][b^1] %= mod;
                                            }
                                            if(f==20){
                                                dp[i][j][m][l^1][h][d][g][c][b] += dp[i-1][j][m][l][h][d][g][c][b];
                                                dp[i][j][m][l^1][h][d][g][c][b] %= mod;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    ll a = dp[n][0][0][0][0][0][0][0][0];
    ll b = k;
    for(ll i =2; i<=n; i++){
        b*=k;
        b%=mod;
    }
    a *= rev(b);
    a%=mod;
    cout << a << endl;

}
