// https://vjudge.net/problem/UVA-988

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

    int n, tc = 0;
    while (cin >> n) {
        if (tc++) cout << '\n';
        vector<vector<int>> adj(n);
        vector<int> indegree(n, 0);
        for (int i=0; i<n; i++) {
            int k, x; cin >> k;
            while (k-- > 0) {
                cin >> x;
                adj[i].push_back(x);
                indegree[x]++;
            }
        }

        queue<int> q;
        vector<int> queries;
        vector<int> dp(n, 0);
        for (int i=0; i<n; i++) {
            if (indegree[i] == 0)
                q.push(i), dp[i] = 1;
            if (adj[i].size() == 0) queries.push_back(i);
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (auto &v : adj[u]) {
                indegree[v]--;
                dp[v] += dp[u];
                if (indegree[v] == 0)
                    q.push(v);
            }
        }

        int ans = 0;
        for (auto &u : queries)
            ans += dp[u];

        cout << ans << endl;
    }

    return 0;
}