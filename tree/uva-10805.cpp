// https://vjudge.net/problem/UVA-10805

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc, t = 1; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> dp(n, vector<int>(n, 1e9));

        for (int i=0; i<m; i++) {
            int u, v;
            cin >> u >> v;
            dp[u][v] = 1, dp[v][u] = 1;
        }

        for (int i=0; i<n; i++) dp[i][i] = 0;

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                for (int k=0; k<n; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }

        for (int i=0; i<n; i++) sort(dp[i].begin(), dp[i].end(), greater<int>());

        int ans = 1e9;
        for (int i=0; i<n; i++) ans = min(ans, dp[i][0] + dp[i][1]);

        printf("Case #%d:\n", t++);
        printf("%d\n\n", ans);
    }

    return 0;
}