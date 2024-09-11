// https://open.kattis.com/problems/equivalences

#include <bits/stdc++.h>
using namespace std;

vector<int> dfs_num, S;
vector<vector<int>> adj, adj_t;

void kosaraju(int u, int pass, int cnt, vector<int>& SCC) {
    dfs_num[u] = cnt;

    if (pass == 1) {
        SCC.push_back(u);
    }

    vector<int>& neightbors = (pass == 0 ? adj[u] : adj_t[u]);
    for (auto &v : neightbors) {
        if (dfs_num[v] == -1) kosaraju(v, pass, cnt, SCC);
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

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        if (m == 0) {
            cout << n << '\n';
            continue;
        }

        adj.assign(n + 1, {});
        adj_t.assign(n + 1, {});
        S.clear();

        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj_t[v].push_back(u);
        }

        dfs_num.assign(n + 1, -1);

        int cnt = 0;

        vector<int> SCC;
        vector<vector<int>> SCCs;
        for (int i=1; i<=n; i++) {
            if (dfs_num[i] == -1) {
                kosaraju(i, 0, cnt, SCC);
                cnt++;
            }
        }

        cnt = 0;

        dfs_num.assign(n + 1, -1);
        for (int i=S.size() - 1; i>=0; i--) {
            if (dfs_num[S[i]] == -1) {
                SCC.clear();
                kosaraju(S[i], 1, cnt, SCC);

                SCCs.push_back(SCC);
                cnt++;
            }
        }

        vector<int> ind(cnt + 5, 0), oud(cnt + 5, 0);
        for (int i=0; i<SCCs.size(); i++) {
            auto s = SCCs[i];
            for (auto &u : s) {
                for (auto &v : adj[u]) {
                    if (dfs_num[u] != dfs_num[v]) {
                        oud[dfs_num[u]]++;
                        ind[dfs_num[v]]++;
                    }
                }
            }
        }

        // cout << "SCCs size : " << SCCs.size() << '\n';

        int ans = 0;
        for (int i=0; i<SCCs.size() - 1; i++) {
            if (ind[i] == 0 || oud[i] == 0) ans++;
        }

        cout << ans << '\n';
    }

    return 0;
}