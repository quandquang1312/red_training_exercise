// https://codeforces.com/contest/1919/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 3e18;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> arr(n + 1);
        for (int i=1; i<=n; i++) cin >> arr[i];

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;

        /*
            dp[i][j]: minimum penalty where
                - the last element of s1 is i
                - the last element of s2 is j
        */

        for (int i=0; i<=n; i++) {
            for (int j=0; j<=n; j++) {
                if (dp[i][j] == INF || (max(i, j) + 1 > n)) continue;
                int idx = max(i, j) + 1;

                // add idx to s1
                int cost1 = (i && (arr[i] < arr[idx]));
                dp[idx][j] = min(dp[idx][j], dp[i][j] + cost1);

                // add idx to 2
                int cost2 = (j && (arr[j] < arr[idx]));
                dp[i][idx] = min(dp[i][idx], dp[i][j] + cost2);
            }
        }

        int ans = INF;
        for (int i=0; i<=n; i++) {
            ans = min(ans, dp[n][i]);
        }

        cout << ans << "\n";
    }

    return 0;
}
