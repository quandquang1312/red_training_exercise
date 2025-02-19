// https://atcoder.jp/contests/abc212/tasks/abc212_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD  = 998244353;
const int MAXN = 5010;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> adj(n + 1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(n + 1, 0), last_dp(n + 1, 0);

    // dp[j] the number of ways to end up at j after k step
    dp[1] = 1;

    for (int i=1; i<=k; i++) {
        int sm = 0LL;
        for (int j=1; j<=n; j++) sm += dp[j];
        for (int j=1; j<=n; j++) {
            last_dp[j] = sm - dp[j]; // n.o ways to reach j from other nodes
            for (auto &v : adj[j]) {
                last_dp[j] -= dp[v]; // exclude unusable road
            }

            last_dp[j] %= MOD;
        }

        for (int j=1; j<=n; j++) dp[j] = last_dp[j];
    }

    cout << dp[1] << "\n";

    return 0;
}
