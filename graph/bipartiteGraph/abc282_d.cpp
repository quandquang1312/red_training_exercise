// https://atcoder.jp/contests/abc282/tasks/abc282_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> color, visited, indegree;

pair<int, int> dfs(int u, int par) {
    if (visited[u] == true) return {0, 0};
    visited[u] = true;

    pair<int, int> ans = {1, indegree[u]};
    for (auto &v : adj[u]) {
        if (v == par || visited[v]) continue;
        pair<int, int> tmp_ans = dfs(v, u);
        ans.first  += tmp_ans.first;
        ans.second += tmp_ans.second;
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

    adj.resize(n+1);
    color.resize(n+1, 2);
    visited.resize(n+1);
    indegree.resize(n+1, 0);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        indegree[v]++;
    }

    vector<int> CCs;
    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            CCs.push_back(i);
            pair<int, int> tmp = dfs(i, 0);
        }
    }

    vector<pair<int, int>> ans;
    bool isBipartite = true;

    for (int idx = 0; idx<CCs.size(); idx++) {
        int rt = CCs[idx];
        queue<int> q;
        q.push(rt);
        color[rt] = 0;

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

        if (isBipartite) ans.push_back(p);
        else break;
    }

    int res = (n * (n - 1)) / 2;
    if (isBipartite) {
        for (int i=0; i<ans.size(); i++) {
            int n1node = (ans[i].first * (ans[i].first - 1)) / 2;
            int n2node = (ans[i].second * (ans[i].second - 1)) / 2;

            res -= n1node;
            res -= n2node;
        }
    }

    cout << (isBipartite ? res - m : 0) << endl;

    return 0;
}