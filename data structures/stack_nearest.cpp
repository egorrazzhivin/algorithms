vector<int> mx_right(n,1e9), mn_right(n,1e9);
stack<pair<int,int>> st;
st.push(make_pair(a.back(),n-1));
for(int i =n-2;i>=0;i--){
    int cur = a[i];
    while(!st.empty() && st.top().first<cur) st.pop();
    if(!st.empty()) mx_right[i] = st.top().second;
    st.push(make_pair(cur,i));
}
while(!st.empty()) st.pop();
st.push(make_pair(a.back(),n-1));
for(int i =n-2;i>=0;i--){
    int cur = a[i];
    while(!st.empty() && st.top().first>cur) st.pop();
    if(!st.empty()) mn_right[i] = st.top().second;
    st.push(make_pair(cur,i));
}
