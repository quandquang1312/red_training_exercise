// https://vjudge.net/problem/UVA-11838

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, adj_t;
vector<int> dfs_num, S;
int n, m;

void kosaraju(int u, int pass)
{
    dfs_num[u] = 1;
    vector<int>& neightbors = (pass == 0 ? adj[u] : adj_t[u]);

    for (auto &v : neightbors) {
        if (dfs_num[v] == -1) 
            kosaraju(v, pass);
    }

    S.push_back(u);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    n = 1, m = 1;
    while ((cin >> n >> m), n) {
        adj.clear(), adj_t.clear();
        adj.resize(n+1);
        adj_t.resize(n+1);
        dfs_num.assign(n+1, -1);

        int a, b, t;
        for (int i=0; i<m; i++) {
            cin >> a >> b >> t;
            adj[a].push_back(b);
            adj_t[b].push_back(a);
            if (t == 2) {
                adj[b].push_back(a);
                adj_t[a].push_back(b);
            }
        }

        S.clear();
        dfs_num.assign(n+1, -1);
        for (int i=1; i<=n; i++)
            if (dfs_num[i] == -1) kosaraju(i, 0);

        int ans = 0;
        dfs_num.assign(n+1, -1);
        for (int i=S.size()-1; i>=0; i--) {
            if (dfs_num[S[i]] == -1) {
                kosaraju(S[i], 1);
                ans++;
            }
        }

        cout << (ans == 1) << endl;
    }

    return 0;
}