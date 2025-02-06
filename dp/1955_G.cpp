// https://codeforces.com/problemset/problem/1955/G

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                cin >> grid[i][j];
            }
        }

        int G = __gcd(grid[1][1], grid[n][m]);
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        auto check = [&] (int g) -> bool {
            dp.assign(n + 1, vector<bool>(m + 1, false));
            dp[1][1] = true;

            for (int i=1; i<=n; i++) {
                for (int j=1; j<=m; j++) {
                    if (grid[i][j] % g != 0) continue;

                    dp[i][j] = dp[i][j] | dp[i-1][j];
                    dp[i][j] = dp[i][j] | dp[i][j-1];
                }
            }

            return dp[n][m];
        };

        int ans = 1;
        for (int x=1; x*x<=G; x++) {
            if (G % x != 0) continue;
            if (check(x)) ans = max(ans, x);
            if (check(G/x)) {
                ans = max(ans, G/x);
                break;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}