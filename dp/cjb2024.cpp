// https://codejam.lge.com/contest/problem/1274/2

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

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
        int n, b, c;
        cin >> n >> b >> c;

        int p[n+1], f[n+1], d[n+1], dp[n+1][c+1];
        for (int i=0; i<n; i++) cin >> p[i];
        for (int i=0; i<n; i++) cin >> f[i];
        for (int i=0; i<n; i++) cin >> d[i];

        for (int i=0; i<=n; i++) {
            for (int j=0; j<=c; j++) {
                dp[i][j] = INF;
            }
        }

        dp[0][b] = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<=c; j++) {
                if (dp[i][j] == INF) continue;
                if (j - d[i] >= 0) dp[i+1][j-d[i]] = min(dp[i+1][j-d[i]], dp[i][j]); // use
                dp[i+1][min(j+p[i], c)] = min(dp[i+1][min(j+p[i], c)], dp[i][j] + d[i]*f[i]); // charge
            }
        }

        int ans = INF;
        for (int i=b; i<=c; i++) {
            ans = min(ans, dp[n][i]);
        }

        cout << ans << endl;
    }
    return 0;
}