// https://cses.fi/problemset/task/1139

#include <bits/stdc++.h>
using namespace std;

vector<int> colors, ans;
vector<vector<int>> adj;
vector<set<int>> dis_col;

void dfs(int u, int par) {
    dis_col[u].insert(colors[u]);
    for (auto &v : adj[u]) {
        if (v == par) continue;

        dfs(v, u);
        if (dis_col[u].size() < dis_col[v].size()) swap(dis_col[u], dis_col[v]);
        for (auto &i : dis_col[v]) dis_col[u].insert(i);
    }

    ans[u] = dis_col[u].size();
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    colors.resize(n + 1);
    adj.resize(n + 1);
    dis_col.resize(n + 1);
    ans.resize(n + 1);

    for (int i=1; i<=n; i++) {
        cin >> colors[i];
    }

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    dfs(1, 0);
    for (int i=1; i<=n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}