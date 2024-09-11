// https://vjudge.net/problem/UVA-11709

#include <bits/stdc++.h>
using namespace std;

void kosaraju(int u, int pass, vector<int>& dfs_num, vector<vector<int>>& neightbors, vector<int>& S) {
    dfs_num[u] = 1;
    for (auto &v : neightbors[u]) {
        if (dfs_num[v] == -1) kosaraju(v, pass, dfs_num, neightbors, S);
    }

    S.push_back(u);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 & m == 0) break;

        vector<vector<int>> adj(n), adj_t(n);
        unordered_map<string, int> idx;
        vector<int> dfs_num(n, -1), S;
        int timer = 0;

        cin.ignore();
        
        for (int i=0; i<n; i++) {
            string str;
            getline(cin, str);
            idx[str] = timer++;
        }

        for (int i=0; i<m; i++) {
            string stru, strv;
            getline(cin, stru);
            getline(cin, strv);

            int u = idx[stru], v = idx[strv];
            adj[u].push_back(v);
            adj_t[v].push_back(u);
        }

        for (int i=0; i<n; i++) {
            if (dfs_num[i] == -1) {
                kosaraju(i, 0, dfs_num, adj, S);
            }
        }

        int ans = 0;
        dfs_num.assign(n, -1);
        for (int i=S.size()-1; i>=0; i--) {
            if (dfs_num[S[i]] == -1) {
                ans++;
                kosaraju(S[i], 1, dfs_num, adj_t, S);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}