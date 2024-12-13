// https://codeforces.com/problemset/problem/1526/C1

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e18

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -INF));

    for (int i=0; i<n; i++) cin >> arr[i];

    dp[0][0] = 0;
    if (arr[0] >= 0) dp[0][1] = arr[0];

    for (int i=1; i<n; i++) {
        dp[i][0] = 0;
        for (int j=1; j<=i+1; j++) {
            // choose
            if (dp[i-1][j-1] >= 0 && dp[i-1][j-1] + arr[i] >= 0) 
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + arr[i]);

            // not choose
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
        }
    }

    int ans = 0;
    for (int i=0; i<=n; i++) {
        if (dp[n-1][i] >= 0) ans = max(ans, i);
    }

    cout << ans << "\n";

    return 0;
}