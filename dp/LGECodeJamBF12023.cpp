// https://codejam.lge.com/problem/27361
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 105
#define MAXS 105
#define INF 1e12

int dp[MAXN][MAXN * MAXS];
int n, k, a, b, s[MAXN], cost[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> k >> a >> b;

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                if (j != 0) dp[i][j] = INF;
                else        dp[i][j] = 0;
            }
        }

        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            cost[i] = (s[i] != 1) ? a * (s[i] - 1) * (s[i] - 1) + b : 0;
        }

        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {

                dp[i][j] = min(dp[i][j], dp[i-1][j]); // keep the current stick

                if (j >= s[i] && dp[i-1][j-s[i]] != INF) {
                    dp[i][j] = min(dp[i][j], dp[i-1][j-s[i]] + cost[i]); // use the current stick
                }

                // if the current stick is greater than the number of stick being considered
                // we can consider cut that stick only
                if (j < s[i]) dp[i][j] = min(dp[i][j], cost[i]);
            }
        }

        int ans = INF;
        for (int i=1; i<=n; i++) {
            ans = min(ans, dp[i][k]);
        }
        cout << ans << endl;
    }

    return 0;
}
