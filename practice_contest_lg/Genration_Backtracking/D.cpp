// https://vjudge.net/contest/678673#problem/D

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

    int n, w;
    cin >> n >> w;
    vector<pair<int, int>> arr(n);

    for (int i=0; i<n; i++) cin >> arr[i].first >> arr[i].second;

    vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));

    for (int i=0; i<n; i++) {
        for (int j=0; j<=w; j++) {
            if (j - arr[i].first >= 0)
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - arr[i].first] + arr[i].second);
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }
    }

    cout << dp[n][w] << "\n";

    return 0;
}