// https://open.kattis.com/problems/birthday

#include <bits/stdc++.h>
using namespace std;

vector<set<int>> adj;
vector<int> dfs_num, dfs_low;
vector<bool> visited;
int timer = 0, b;

void dfs(int u, int p = -1)
{
    if (b >= 1) return;
    dfs_num[u] = dfs_low[u] = timer++;

    bool parent_skipped = false;
    for (auto &v : adj[u]) {
        if (b >= 1) break;
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

    if (b >= 1) return;
}

void connected(int u, int p) {
    if (visited[u]) return;
    visited[u] = true;
    for (auto &v : adj[u]) {
        if (v == p || visited[v]) continue;
        connected(v, u);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n = 1, m = 1;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0) break;

        adj.assign(n, {});
        dfs_num.assign(n, -1);
        dfs_low.assign(n, 0);
        visited.assign(n, false);
        timer = 0, b = 0;

        int src, dst;
        for (int i=0; i<m; i++) {
            cin >> src >> dst;
            adj[src].insert(dst);
            adj[dst].insert(src);
        }

        connected(0, -1);

        int cnt = 0;
        bool fl = true;
        for (int i=0; i<n; i++) {
            if (!visited[i]) {
                fl = false;
                break;
            }
        }

        if (!fl) {
            cout << "Yes\n";
            continue;
        }

        for (int i=0; i<n && b < 1; i++) {
            if (dfs_num[i] == -1) dfs(i);
        }

        cout << (b >= 1 ? "Yes\n" : "No\n");
    }

    return 0;
}