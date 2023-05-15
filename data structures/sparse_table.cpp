vector<vector<int>> sparse(20, vector<int>(n));
        for(int i =0;i<n;i++){
            sparse[0][i] = a[i];
        }
        for(int sz=1; sz<=19;sz++){
            for(int i =0;i+(1<<sz)<=n;i++){
                sparse[sz][i] = max(sparse[sz-1][i], sparse[sz-1][i+(1<<(sz-1))]);
            }
        }
        vector<int> log(n + 1);
        log[0] = log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }
