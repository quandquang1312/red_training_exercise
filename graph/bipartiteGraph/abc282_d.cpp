// https://atcoder.jp/contests/abc282/tasks/abc282_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> color, visited;
vector<pair<int, int>> dp;

int dfs(int u, int par) {
    if (visited[u] == true) return 0;
    visited[u] = true;

    int ans = 1;
    for (auto &v : adj[u]) {
        if (v == par || visited[v]) continue;
        ans += dfs(v, u);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    dp.resize(n + 1, {-1, -1});
    vector<int> sz(n + 1, -1);
    color.resize(n + 1, 2);
    visited.resize(n + 1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> CCs;
    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            CCs.push_back(i);
            sz[i] = dfs(i, 0);
        }
    }

    vector<pair<int, int>> ans;
    for (auto rt : CCs) {
        // cout << rt << ": " << sz[rt] << '\n';
        return 0;
        queue<int> q;
        q.push(rt);
        color[rt] = 0;

        bool isBipartite = true;
        pair<int, int> p;
        while (!q.empty() && isBipartite)
        {
            int u = q.front(); q.pop();

            if (color[u] == 0) p.first++;
            else p.second++;

            for (auto &v : adj[u]) {
                if (color[v] == 2) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    isBipartite = false;
                    break;
                }
            }
        }

        if (!isBipartite) { }
        else {
            ans.push_back(p);
        }
    }

    int res = 0;
    for (int i=0; i<ans.size(); i++) {
        res += (ans[i].first * ans[i].second) - noe;
        for (int j=i+1; j<ans.size(); j++) {
            res += ans[i].first * ans[j].second;
            res += ans[i].second * ans[j].first;
        }
    }

    cout << res << endl;

    return 0;
}