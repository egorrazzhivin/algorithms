/*
cute problem from cses
https://cses.fi/problemset/task/1670/
*/
int powers[10];
 
int get_hash(string s){
    int n = (int)s.length();
    int hash = 0;
    for(int i =n-1;i>=0;i--){
        hash += (int)(s[i]-'0')*powers[n-1-i];
    }
    return hash;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    unordered_map<int, int> lol;
    powers[0] = 1;
    for(int i =1;i<=8;i++) powers[i] = powers[i-1]*10;
    string s = "123456789";
    string ans = string(9,'0');
    for(int i =0;i<9;i++) cin >> ans[i];
    lol[get_hash(s)] = 0;
    //cout << "ans = " << ans << endl;
    queue<int> q;
    q.push(get_hash(s));
    while(!q.empty()){
        int hs = q.front();
        string cur = to_string(hs);
        q.pop();
        for(int i =0;i<9;i++){
            if(i%3!=2){
                int cur_hash = hs + (cur[i+1]-cur[i])*powers[8-i] + (cur[i]-cur[i+1])*powers[8-(i+1)];
                if(!lol.count(cur_hash)){
                    lol[cur_hash] = lol[hs] + 1;
                    q.push(cur_hash);
                }
            }
            if(i<6){
                
                int cur_hash = hs + (cur[i+3]-cur[i])*powers[8-i] + (cur[i]-cur[i+3])*powers[8-(i+3)];
                if(!lol.count(cur_hash)){
                    lol[cur_hash] = lol[hs]+1;
                    q.push(cur_hash);
                }
            }
        }
    }
    cout << lol[get_hash(ans)] << endl;
}
