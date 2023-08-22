/*
https://www.spoj.com/problems/DOM/
nice dp problem
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> h(n+1,0);
        for(int i = 1;i<=n;i++) cin >> h[i];
        vector<int> right(n+1, -1), left(n+1, -1);
        vector<int> x(n+1,0);
        for(int i = 2;i<=n;i++){
            int p;
            cin >> p;
            x[i] = x[i-1] + p;
        }
        if(n==1){
            cout << 1 << endl;
            cout << 1 << " " << 'L' << endl;
            continue;
        }
        for(int i = 1;i<=n;i++){
            //find such max j that we can achieve it by dropping i to the right
            int mx = i;
            int cur_coord = x[i]+h[i];
            for(int j = i+1;j<=n;j++){
                if(cur_coord < x[j]) break;
                else{
                    cur_coord = max(cur_coord, x[j]+h[j]);
                    mx = j;
                }
            }
            right[i] = mx;
        }
        for(int i = n;i>=1;i--){
            //find such min j that we can achieve it by dropping i to the left
            int mx = i;
            int cur_coord = x[i]-h[i];
            for(int j = i-1;j>=1;j--){
                if(cur_coord > x[j]) break;
                else{
                    cur_coord = min(cur_coord, x[j]-h[j]);
                    mx = j;
                }
            }
            left[i] = mx;
        }
        vector<pair<int, int>> dp(n+1, make_pair(1001, -1));
        vector<pair<int,char>> side(n+1, make_pair(-1, 'S'));
        dp[n] = make_pair(1, n+1);
        side[n] = make_pair(n, 'L');
        for(int i = n-1;i>=1;i--){
            //in optimal strategy on the suffix [i,n] we can move from i to right[i]
            int nxt = right[i];
            if(nxt==n){
                dp[i] = make_pair(1, n+1);
                side[i] = make_pair(i,'R');
            }
            else{
                dp[i] = make_pair(1+dp[nxt+1].first, nxt+1);
                side[i] = make_pair(i,'R');
            }
            for(int j = i + 1; j<=n;j++){
                int leftmost = left[j];
                //or we can move from i to j+1 if from j we can get i
                if(leftmost<=i){
                    //we can achieve i from j
                    if(j!=n && dp[j+1].first + 1 < dp[i].first){
                        dp[i] = make_pair(dp[j+1].first + 1, j+1);
                        side[i] = make_pair(j, 'L');
                    }
                    else if(j==n && dp[j].first < dp[i].first){
                        dp[i] = make_pair(dp[j].first, j+1);
                        side[i] = make_pair(j, 'L');
                    }
                }
            }
        }
        vector<pair<int, char>> ans;
        int cur = 1;
        while(cur<=n){
            auto p = dp[cur];
            ans.push_back(side[cur]);
            cur = p.second;
        }
        cout << ans.size() << endl;
        for(auto p : ans){
            if(p.second == 'R'){
                cout << p.first << " " << 'P' << endl;
            }
            else cout << p.first << " " << p.second << endl;
        }
    }
} 

