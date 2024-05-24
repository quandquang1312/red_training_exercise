// https://atcoder.jp/contests/abc350/tasks/abc350_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<bool> visited;
int edge[200010] {};

void dfs(int v, vector<int>& cc) {
    visited[v] = true;
    cc.push_back(v);

    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u, cc);
        }
    }
}

vector<vector<int>> findCC(int n) {
    vector<vector<int>> components;

    visited.assign(n + 1, false);

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            vector<int> cc;
            dfs(i, cc);
            components.push_back(cc);
        }
    }

    return components;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge[u]++;
    }

    vector<vector<int>> components = findCC(n);

    // cout << "cc: " << components.size() << "\n";
    int res = 0LL;
    for (auto& cc : components) {
        // cout << "c: ";
        int sz = cc.size(), ed = 0;
        for (int node : cc) {
            // cout << node << " ";
            ed += edge[node];
        }
        int tt = (sz * (sz - 1))/2;
        // cout << ", e: " << ed << ", ans: " << (tt - ed) << endl;
        res += (tt - ed);
    }

    cout << res << endl;

    return 0;
}
