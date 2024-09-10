// https://vjudge.net/problem/UVA-315

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> dfs_num, dfs_low, articulation, parent;
int timer, rootChildren, root;

#define UNVISITED -1

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

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

int find_articulation_point(int n)
{
    timer = 0;
    parent.assign(n + 1, -1);
    dfs_low.assign(n + 1, 0);
    dfs_num.assign(n + 1, UNVISITED);
    articulation.assign(n + 1, 0);

    for (int i=1; i<=n; i++) {
        if (dfs_num[i] == UNVISITED) {
            root = i, rootChildren = 0;
            dfs(i);
            articulation[root] = (rootChildren > 1);
        }
    }

    int ans = 0;
    for (int i=1; i<=n; i++) ans += articulation[i];
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n;
    while (cin >> n) {
        if (n == 0) break;
        cin.ignore();

        adj.assign(n + 1, {});
        string str;
        while (getline(cin, str), str != "0") {
            stringstream ss(str);
            int u, v;
            ss >> u;

            while (ss >> v) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        // for (int i=1; i<=n; i++) {
        //     cout << i << ": ";
        //     for (auto &e : adj[i]) {
        //         cout << e << " ";
        //     }
        //     cout << endl;
        // }

        int ans = find_articulation_point(n);
        cout << ans << '\n';
    }

    return 0;
}