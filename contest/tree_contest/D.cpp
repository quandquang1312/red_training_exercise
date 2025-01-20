// https://codeforces.com/gym/102694/problem/B
// Min weight on the path from u to v
// LCA min weight

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOG = 22;

vector<pair<int, int>> adj[MAXN];

int up[MAXN][LOG];
int minEdge[MAXN][LOG];
int depth[MAXN];

void dfs(int node, int parent, int weight, int d) {
    up[node][0] = parent;
    minEdge[node][0] = weight;
    depth[node] = d;

    for (int j = 1; j < LOG; j++) {
        if (up[node][j-1] != -1) {
            up[node][j] = up[up[node][j-1]][j-1];
            minEdge[node][j] = min(minEdge[node][j-1], minEdge[up[node][j-1]][j-1]);
        } else {
            up[node][j] = -1;
            minEdge[node][j] = INT_MAX;
        }
    }

    for (auto [child, w] : adj[node]) {
        if (child != parent) {
            dfs(child, node, w, d + 1);
        }
    }
}

int minEdgeQuery(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    int minWeight = INT_MAX;

    int diff = depth[u] - depth[v];
    for (int i = LOG - 1; i >= 0; i--) {
        if ((diff >> i) & 1) {
            minWeight = min(minWeight, minEdge[u][i]);
            u = up[u][i];
        }
    }

    if (u == v) return minWeight;

    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            minWeight = min(minWeight, min(minEdge[u][i], minEdge[v][i]));
            u = up[u][i];
            v = up[v][i];
        }
    }

    minWeight = min(minWeight, min(minEdge[u][0], minEdge[v][0]));
    return minWeight;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, q;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    dfs(1, -1, INT_MAX, 0);

    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << minEdgeQuery(u, v) << endl;
    }

    return 0;
}
