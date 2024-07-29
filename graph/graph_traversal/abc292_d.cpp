// https://atcoder.jp/contests/abc292/tasks/abc292_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1), CCs;
    vector<int> indegree(n+1, 0);
    for (int i=0; i<m; i++) {
        int u, v; cin >> u >> v;
        indegree[u]++;
        adj[u].push_back(v);
        if (u != v) adj[v].push_back(u);
    }

    vector<bool> visited(n+1, false);
    queue<int> q;
    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            vector<int> cc;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                cc.push_back(u);
                for (auto &v : adj[u]) {
                    if (visited[v]) continue;
                    q.push(v);
                    visited[v] = true;
                }
            }
            CCs.push_back(cc);
        }
    }

    string ans = "Yes";
    for (auto &cc : CCs) {
        int sm_edge = 0;
        for (auto &e : cc) sm_edge += indegree[e];
        if (sm_edge != cc.size()) {
            ans = "No";
            break;
        }
    }

    cout << ans << endl;


    return 0;
}