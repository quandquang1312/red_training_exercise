// https://open.kattis.com/problems/birthday

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> dfs_num, dfs_low;
int timer, b;

void dfs(int u, int p = -1)
{
    dfs_num[u] = dfs_low[u] = timer++;

    bool parent_skipped = false;
    for (auto &v : adj[u]) {
        if (v == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }

        if (dfs_num[v] == -1) {
            dfs(v, u);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);

            if (dfs_low[v] > dfs_num[u]) b++;
        } else {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n = 1, m = 1;
    while ((cin >> n >> m), n && m)
    {
        adj.resize(n+1);
        dfs_num.assign(n+1, -1);
        dfs_low.assign(n+1, 0);
        timer = 0, b = 0;

        int src, dst;
        for (int i=0; i<m; i++) {
            cin >> src >> dst;
            adj[src].push_back(dst);
            adj[dst].push_back(src);
        }

        for (int i=0; i<n; i++) {
            if (dfs_num[i] == -1) {
                dfs(i);
            }
        }

        cout << (b >= 1 ? "Yes\n" : "No\n");
    }

    return 0;
}