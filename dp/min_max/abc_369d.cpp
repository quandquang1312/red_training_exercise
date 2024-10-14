// https://atcoder.jp/contests/abc369/tasks/abc369_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n + 1);
    for (int i=1; i<=n; i++) cin >> arr[i];

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    dp[1][0] = arr[1];

    for (int i=2; i<=n; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] + arr[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] + arr[i] * 2);
    }

    cout << max(dp[n][0], dp[n][1]) << "\n";

    return 0;
}