/*
fun combinatorics problem
link: https://codeforces.com/contest/1511/problem/E?locale=en
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
 
const int mod = 998244353; //prime
const ll inf = 1e18;

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
    vector<ll> dp(300300,0);
    ll four = rev(4);
    ll two = rev(2);
    dp[1] = rev(4);
    dp[2] = rev(8);
    //dp[3]=(3*rev(16))%mod;
    ll odd = dp[1];
    ll even = dp[2];
    for(int k=3;k<=300200;k++){
        if(k%2){
            dp[k] = (rev(4)*(rev(2)+odd))%mod;
            odd=dp[k];
        }
        else{
            dp[k]=(rev(4)*(rev(2)+even))%mod;
            even=dp[k];
        }
    }
    int n,m;
    cin >> n >> m;
    int total = 0;
    vector<vector<int>> table(n, vector<int>(m,0));
    for(int i =0;i<n;i++){
        for(int j=0;j<m;j++){
            char c;
            cin >> c;
            if(c=='o') {
                table[i][j]=1;
                total++;
            }
        }
    }
    ll ans = 0;
    for(int i =0;i<n;i++){
        vector<int> tmp = table[i];
        tmp.push_back(0);
        int ones = 0;
        for(int j=0;j<m;j++){
            if(tmp[j]) {
                if(tmp[j+1]) {
                    ones++;
                    ans+=dp[ones];
                    ans%=mod;
                    
                    
                }
            }
            else{
                //cout << "ones = " << ones << endl;
                //ans+=dp[ones];
                ans%=mod;
                ones=0;
            }
        }
    }
    vector<vector<int>> transposed_table(m, vector<int>(n,0));
    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            transposed_table[j][i] = table[i][j];
        }
    }  
    for(int i =0;i<m;i++){
        vector<int> tmp = transposed_table[i];
        tmp.push_back(0);
        int ones = 0;
        for(int j=0;j<n;j++){
            if(tmp[j]) {
                if(tmp[j+1]){
                    ones++;
                    ans+=dp[ones];
                    ans%=mod;
                    
                    
                }   
            }
            else{
                ans%=mod;
                ones=0;
            }
        }
    }
    //cout << "ans = " << ans << endl;
    for(int i =0;i<total;i++){
        ans*=2;
        ans%=mod;
    }
    cout << ans << endl;
}
