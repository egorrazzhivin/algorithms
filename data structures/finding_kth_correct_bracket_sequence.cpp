//finding kth correct bracket sequence
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool isSmaller(string str1, string str2){
    int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
    return false;
}

string add(string str1, string str2){
    if (str1.length() > str2.length()) swap(str1, str2);
    string str;
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n1; i++){
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    for (int i=n1; i<n2; i++){
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry) str.push_back(carry+'0');

    reverse(str.begin(), str.end());
    return str;
}

string subtract(string str1, string str2){
    if (isSmaller(str1, str2)) swap(str1, str2);
    string str;
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i = 0; i < n2; i++) {
        int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else carry = 0;
        str.push_back(sub + '0');
    }
    for (int i = n2; i < n1; i++) {
        int sub = ((str1[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else carry = 0;
        str.push_back(sub + '0');
    }
    reverse(str.begin(), str.end());
    int i = 0;
    while(str[i]=='0') i++;
    string res;
    while(i!=(int)str.length()){
        res += str[i];
        i++;
    }
    return res;
}

string dp[202][202];

int main(){
    int n;
    cin >> n;
    string k;
    cin >> k;
    for(int i = 0;i<=2*n;i++) {
        for(int j = 0;j<=2*n;j++) dp[i][j] = "0";
    }
    dp[0][0] = "1";
    for(int i = 1;i<=2*n;i++){
        for(int j = 0;j<=2*n;j++){
            if(j) dp[i][j] = add(dp[i][j], dp[i-1][j-1]);
            if(j<2*n) dp[i][j] = add(dp[i][j], dp[i-1][j+1]);
        }
    }
    if(isSmaller(dp[2*n][0],k)) {
        cout << "No solution for this testcase." << endl;
        return 0;
    }
    string ans;
    int depth = 0;
    for(int i = 2*n-1;i>=0;i--){
        if(!isSmaller(dp[i][depth+1],k)){
            ans += '(';
            depth++;
        }
        else{
            ans += ')';
            string new_k = subtract(k, dp[i][depth+1]);
            k = new_k;
            depth--;
        }
    }
    cout << ans << endl;
}
