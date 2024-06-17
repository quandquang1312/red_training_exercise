// https://cses.fi/problemset/task/1093

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    int target = n * (n+1);
    if (target % 4) {
        cout << "0\n";
        return 0;
    }

    target /= 4;

    int dp[n+1][target+1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;

    for (int i=1; i<=n; i++) {
        for (int s=0; s<=target; s++) {
            dp[i][s] = dp[i-1][s]; // not choose i

            if (s - i >= 0) {
                dp[i][s] += dp[i-1][s-i] % MOD;
                dp[i][s] %= MOD;
            }
        }
    }

    cout << dp[n][target] / 2 << endl;

    return 0;
}