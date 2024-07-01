// https://vjudge.net/problem/UVA-12783

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> dfs_low, dfs_num, parent;
vector<pair<int, int>> bridges;
int timer;

void findBridges(int u, int p = -1)
{
    dfs_num[u] = dfs_low[u] = timer++;

    bool parent_skipped = false;
    for (auto &v : adj[u]) {
        if (v == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }

        if (dfs_num[v] == -1) {
            findBridges(v, u);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
            if (dfs_low[v] > dfs_num[u])
            {
                int tmp_a = min(u, v), tmp_b = max(u,v);
                bridges.push_back({tmp_a, tmp_b});
            }
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
    while ((cin >> n >> m))
    {
        if (n + m == 0) break;
        adj.resize(n);
        dfs_low.assign(n, -1);
        dfs_num.assign(n, -1);
        bridges.clear();
        timer = 0;

        int a, b;
        for (int i=0; i<m; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        for (int i=0; i<n; i++) {
            if (dfs_num[i] == -1)
                findBridges(i, -1);
        }

        sort(bridges.begin(), bridges.end(), [](pair<int, int> p1, pair<int, int> p2) {
            if (p1.first == p2.first) return p1.second < p2.second;
            return p1.first < p2.first;
        });

        printf("%d", bridges.size());
        for (auto &e : bridges) printf(" %d %d", e.first, e.second);
        printf("\n");
    }

    return 0;
}