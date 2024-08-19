// https://cses.fi/problemset/task/1681

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1);
    
    vector<int> indegree(n+1, 0), dp(n+1, 0);
    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;
    for (int i=1; i<=n; i++) if (indegree[i] == 0) q.push(i);
    dp[1] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &v : adj[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }

    cout << dp[n] << '\n';

    return 0;
}