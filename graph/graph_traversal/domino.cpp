// https://open.kattis.com/problems/dominos

#include <bits/stdc++.h>
using namespace std;

int n, m, ans;

void dfs(int u, vector<bool>& visited, vector<vector<int>>& adj) {
    if (visited[u]) return;
    visited[u] = true;

    for (auto &v : adj[u])
        dfs(v, visited, adj);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--)
    {
        cin >> n >> m;

        vector<vector<int>> adj(n+1);
        vector<int> indegree(n+1, 0);

        int a, b;
        for (int i=0; i<m; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
            indegree[b]++;
        }

        queue<int> q;
        ans = 0;
        for (int i=1; i<=n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        ans += q.size();

        while (!q.empty())
        {
            int u = q.front(); q.pop();

            for (auto &v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }

    return 0;
}