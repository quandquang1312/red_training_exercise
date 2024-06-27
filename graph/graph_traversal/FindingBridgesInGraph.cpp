// https://oj.vnoi.info/problem/graph_

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> dfs_num, dfs_low, articulation, parent;
vector<pair<int, int>> bridges;
int timer, n, m, rootChildren, root;
int cnt_b = 0, cnt_a = 0;

#define UNVISITED -1
/*
8 6
0 1
1 3
1 2
2 3
3 4
6 7
*/

void dfs(int u)
{
    dfs_num[u] = dfs_low[u] = timer++;

    for (auto v : adj[u])
    {
        if (dfs_num[v] == UNVISITED) {
            parent[v] = u;

            if (u == root) ++rootChildren;

            dfs(v);

            if (dfs_low[v] >= dfs_num[u])
                articulation[u] = 1;
            if (dfs_low[v] > dfs_num[u])
                cnt_b++;
                // bridges.push_back({u, v});

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

void find_bridges()
{
    timer = 0;
    visited.resize(n+1, false);
    parent.resize(n+1, -1);
    dfs_low.resize(n+1, 0);
    dfs_num.resize(n+1, UNVISITED);
    articulation.resize(n+1, 0);

    for (int i=1; i<=n; i++) {
        if (dfs_num[i] == UNVISITED) {
            root = i, rootChildren = 0;
            dfs(i);
            articulation[root] = (rootChildren > 1);
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

    cin >> n >> m;

    adj.resize(n+1);
    
    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    find_bridges();

    for (int i=1; i<=n; i++)
        if (articulation[i]) cnt_a++;

    cout << cnt_a << " " << cnt_b << endl;

    return 0;
}