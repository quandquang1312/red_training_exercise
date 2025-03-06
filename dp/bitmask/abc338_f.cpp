// https://atcoder.jp/contests/abc338/tasks/abc338_f

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int i=0; i<n; i++) dist[i][i] = 0;

    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        u--, v--;
        dist[u][v] = w;
    }

    // Floyd-Marshall
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if ((dist[i][k] != INF) && (dist[k][j] != INF)) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // dp[mask][j]: walk ends at j and visited all nodes in mask
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    for (int i=0; i<n; i++) dp[1 << i][i] = 0;

    for (int mask=1; mask<(1 << n); mask++) {
        for (int i=0; i<n; i++) {
            if (!(mask & (1 << i))) continue;
            if (dp[mask][i] == INF) continue;

            for (int j=0; j<n; j++) {
                if (dist[i][j] == INF) continue;

                int new_mask = mask | (1 << j);
                dp[new_mask][j] = min(dp[new_mask][j], dp[mask][i] + dist[i][j]);
            }
        }
    }

    int ans = INF;
    for (int i=0; i<n; i++) {
        ans = min(ans, dp[(1 << n) - 1][i]);
    }

    cout << (ans == INF ? "No\n" : to_string(ans)) << "\n";

    return 0;
}
