// https://usaco.org/index.php?page=viewproblem2&cpid=647

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #else
        freopen("248.in", "r", stdin);
        freopen("248.out", "w", stdout);
    #endif

    int n; cin >> n;
    int arr[n];
    for (int i=0; i<n; i++) cin >> arr[i];

    // dp[i][j] is the element that can be merged in he range i->j
    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (int i=n-1; i>=0; i--) {
        dp[i][i] = arr[i];
        for (int j=i+1; j<n; j++) {
            dp[j][j] = arr[j];
            for (int k=i; k<j; k++) {
                if (dp[i][k] != -1) {
                    if (dp[i][k] == dp[k+1][j]) {
                        dp[i][j] = max(dp[i][j], dp[i][k] + 1);
                    }
                }
            }
        }
    }
    
    int ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << '\n';

    return 0;
}