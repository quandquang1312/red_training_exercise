// https://vjudge.net/problem/UVA-12379

#include <bits/stdc++.h>
using namespace std;

#define MAXN 10050
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

    dist.assign(MAXN, 0);
    dfs(1, 0, 0, adj);

    int pos = farthest;
    farthest = 0;
    dist.assign(MAXN, 0);
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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<vector<int>> adj(n+100);

        for (int i=1; i<=n; i++) {
            int sl, v; cin >> sl;
            while (sl--) {
                cin >> v;
                adj[i].push_back(v);
            }
        }

        if (n == 1) {
            cout << "0\n";
            continue;
        }

        int d = diameter(adj);
        cout << 2 * (n - 1) - d << '\n';
    }

    return 0;
}