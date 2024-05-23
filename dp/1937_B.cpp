// https://codeforces.com/problemset/problem/1937/B

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;

    while (tc--) {
        int n; cin >> n;

        char grid[2][n];
        for (int i=0; i<n; i++) cin >> grid[0][i];
        for (int i=0; i<n; i++) cin >> grid[1][i];

        int cut = n-1;
        for (int i=0; i<n-1; i++) {
            if ((grid[0][i+1] - '0') > (grid[1][i] - '0')) {
                cut = i;
                break;
            }
        }

        string ans = "";
        for (int i=0; i<=cut; i++) ans.push_back(grid[0][i]);
        for (int i=cut; i<n; i++)  ans.push_back(grid[1][i]);

        int dp[2][n];
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for (int i=1; i<n; i++) {
            if (grid[0][i] == ans[i]) dp[0][i] = 1;
            else break;
        }

        dp[1][0] = (grid[0][1] >= grid[1][0] ? 1 : 0);

        for (int i=1; i<n; i++) {
            if (grid[1][i] == ans[i+1]) dp[1][i] = dp[0][i] + dp[1][i-1];
        }

        // cout << "start\n";
        // for (int i=0; i<n; i++) cout << dp[0][i];
        // cout << endl;
        // for (int i=0; i<n; i++) cout << dp[1][i];
        // cout << "\nend\n";

        cout << ans << endl;
        cout << dp[1][n-1] << endl;
    }


    return 0;
}