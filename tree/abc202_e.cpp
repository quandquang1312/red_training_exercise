// https://atcoder.jp/contests/abc202/tasks/abc202_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
map<int, vector<int>> depth_val;
vector<int> parent, depth, startIdx, endIdx;
int timer = 0;

void dfs(int u, int prev) {
    startIdx[u] = timer++;
    depth_val[depth[u]].push_back(startIdx[u]);
    for (auto &v : adj[u]) {
        if (v == prev) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
    endIdx[u] = timer++;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    adj.resize(n + 1);
    parent.assign(n + 1, 0);
    depth.assign(n + 1, 0);
    startIdx.assign(n + 1, 0);
    endIdx.assign(n + 1, 0);

    for (int i=2, x; i<=n; i++) {
        cin >> parent[i];
        adj[i].push_back(parent[i]);
        adj[parent[i]].push_back(i);
    }

    dfs(1, 0);

    int q; cin >> q;

    while (q--) {
        int u, d;
        cin >> u >> d;
        if (depth[u] > d) {
            cout << 0 << "\n";
        } else if (depth[u] == d) {
            cout << 1 << "\n";
        } else {
            vector<int> &val = depth_val[d];

            // y is descendant of x if startIdx[x] < startIdx[y] < endIdx[y]
            // so the number of descendant of x in val vector (vector contains nodes that has lenght d)
            // is the number of nodes that has endIdx > startIdx[x] - the number of nodes that has startIdx < startIdx[x]  
            int ans = lower_bound(val.begin(), val.end(), endIdx[u]) - lower_bound(val.begin(), val.end(), startIdx[u]);
            cout << ans << endl;
        }
    }

    return 0;
}