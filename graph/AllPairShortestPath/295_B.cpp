// https://codeforces.com/problemset/problem/295/B

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<int> arr(n), ans(n, 0);

    vector<bool> removed(n, true);
    vector<vector<int>> dp(n, vector<int>(n, INF));

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> dp[i][j];
        }
    }

    for (int i=0; i<n; i++) cin >> arr[i];

    for (int i=n-1; i>=0; i--) {
        removed[arr[i] - 1] = false;
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                if (dp[j][k] > dp[j][arr[i] - 1] + dp[arr[i] - 1][k]) {
                    dp[j][k] = dp[j][arr[i] - 1] + dp[arr[i] - 1][k];
                }
            }
        }

        ans[i] = 0;
        for (int j=0; j<n; j++) {
            if (removed[j]) continue;
            for (int k=0; k<n; k++) {
                if (removed[k]) continue;
                ans[i] += dp[j][k];
            }
        }
    }

    for (int i=0; i<n; i++) cout << ans[i] << " ";
    cout << "\n";

    return 0;
}