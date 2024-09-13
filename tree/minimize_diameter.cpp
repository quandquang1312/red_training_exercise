// https://codeforces.com/gym/104536/problem/F

#include <bits/stdc++.h>
using namespace std;

int farthest = 0;
vector<int> dist;

void dfs(int u, int par, int d, vector<vector<int>> &adj) {
    dist[u] = d;
    if (dist[u] > dist[farthest]) {
        farthest = u;
    }

    for (auto &v : adj[u]) {
        if (v == par) continue;
        dfs(v, u, d + 1, adj);
    }
}

int diameter(vector<vector<int>>& adj) {
    int n = adj.size() - 1;

    farthest = 0;
    dist.assign(n + 1, 0);
    dfs(1, 0, 0, adj);

    int pos = farthest;

    farthest = 0;
    dist.assign(n + 1, 0);
    dfs(pos, 0, 0, adj);

    return dist[farthest];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n;

    vector<vector<int>> tree1(n + 1);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        tree1[u].push_back(v);
        tree1[v].push_back(u);
    }

    int a = diameter(tree1);

    cin >> m;
    vector<vector<int>> tree2(m + 1);

    for (int i=0, u, v; i<m-1; i++) {
        cin >> u >> v;
        tree2[u].push_back(v);
        tree2[v].push_back(u);
    }

    int b = diameter(tree2);

    // c is for merging two tree
    // the nodes we merge are the middle nodes of each tree
    int c = ((a + 1) / 2) + ((b + 1) / 2) + 1;
    
    // we also have to consider the diameters of each tree 
    // for case when the diameter of one tree is larger than when
    // we merge two trees
    cout << max({a, b, c}) << '\n';

    return 0;
}