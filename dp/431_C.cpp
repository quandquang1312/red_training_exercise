// https://codeforces.com/problemset/problem/431/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int n, k, d, ans;
int dp[110][2];

int solve(int remain_sm, bool status_d) {
    if (remain_sm < 0) return 0;
    if (remain_sm == 0) {
        return dp[remain_sm][status_d] = status_d;
    }

    if (dp[remain_sm][status_d] != -1) return dp[remain_sm][status_d];
    dp[remain_sm][status_d] = 0;

    for (int i=1; i<=k; i++) {
        dp[remain_sm][status_d] = (dp[remain_sm][status_d] + solve(remain_sm - i, (status_d || (i >= d))) % MOD) % MOD;
    }

    return dp[remain_sm][status_d];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> k >> d;

    // dp[i][j] : the n.o ways when the remain sum is i and its status is j
    // memset(dp, -1, sizeof dp);

    // int ans = solve(n, false);
    // cout << ans << "\n";

    // memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=k && i>=j; j++) {
            if (j >= d) {
                dp[i][1] = (dp[i][1] + dp[i-j][0]) % MOD;
                dp[i][1] = (dp[i][1] + dp[i-j][1]) % MOD;
            } else {
                dp[i][0] = (dp[i][0] + dp[i-j][0]) % MOD;
                dp[i][1] = (dp[i][1] + dp[i-j][1]) % MOD;
            }
        }
    }

    cout << dp[n][1] << "\n";

    return 0;
}