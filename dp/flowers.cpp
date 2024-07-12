// Problem 1.5.1 (Patrick Zhang, TJ SCT)
#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
11
1 1
2 2
2 1
3 1
3 2
4 2
5 2
6 3
10 3
15 4
20 5

output:
2
4
2
4
6
14
26
42
512
32768
1048576
*/
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<vector<int>> dp(n+1, vector<int>(2, 0));

        dp[0][0] = 1, dp[0][1] = 1;
        for (int i=0; i<=n; i++) {
            for (int j=1; j<=m && i+j<=n; j++) {
                dp[i+j][0] += dp[i][1];
            }
        }

        for (int i=0; i<=n; i++) {
            for (int j=1; j<=m && i+j<=n; j++) {
                dp[i+j][1] += dp[i][0];
            }
        }

        cout << dp[n][0] + dp[n][1] << endl;
    }


    return 0;
}