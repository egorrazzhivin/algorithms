/*
  https://codeforces.com/contest/1312/problem/E
  weird dp, beautiful dp
  anyway need to learn some dp stuff bruh bb
*/
int dp[505][505];
int ans[505];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    /*
        look at a. a = (a-1)merge(a-1);
        each of a-1 is a product of merging of b's such that b<a-1;
        suppose that value of segment [a,b] is not unique
        then we have two different points i,j such that
        f([a,i]) = A = f((i,b])
        f([a,j]) = B = f((j,b])
        if i < j
        then its easy to get contradiction because
        if A<B then we have segment that gives us B>A
        because value at prefix must be lower than value on the whole segment
        but its not good explanation imho

    */
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i =1;i<=n;i++) cin >> a[i];
    for(int i =0;i<=n;i++){
        for(int j =0;j<=n;j++) dp[i][j] = -1;
    }
    for(int i =1;i<=n;i++) dp[i][i] = a[i];
    for(int len = 2;len<=n;len++){
        for(int left = 1; left<=n-len+1;left++){
            int right = left+len-1;
            for(int j = left; j<right;j++){
                if(dp[left][j]!=-1 && dp[left][j]==dp[j+1][right]) dp[left][right] = dp[left][j]+1;
            }
        }
    }
    for(int i =0;i<=n;i++) ans[i] = 1001001;
    ans[0] =0 ;
    ans[1] = 1;
    for(int pref=2;pref<=n;pref++){
        ans[pref] = pref;
        for(int left = 1;left<pref;left++){
            ans[pref] = min(ans[pref], ans[left]+pref-left);
            for(int right = left;right<pref;right++){
                if(dp[left][right]!=-1 && dp[left][right]==dp[right+1][pref]) {
                    ans[pref] = min(ans[pref],ans[left-1]+1);
                    //cout << "pref = " << pref << " left = " << left << " right = " << right << " dp[left][right] = " << dp[left][right] << endl;
                }
            }
        }
    }
    for(int i =1;i<=n;i++){
        //cout << "i = " << i << " dp[i] = " << ans[i] << endl;
    }
    cout << ans[n] << endl;

}
