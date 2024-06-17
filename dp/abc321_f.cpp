// https://atcoder.jp/contests/abc321/tasks/abc321_f

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int q, k;
    cin >> q >> k;

    int dp[q+1][k+1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i=1; i<=q; i++) {
        char c; int x;
        cin >> c >> x;

        if (c == '+')
        {
            for (int j=0; j<=k; j++) {
                dp[i][j] = dp[i-1][j];
                if (j - x >= 0) {
                    dp[i][j] = dp[i][j] + dp[i-1][j-x] % MOD;
                    dp[i][j] %= MOD;
                }
            }
        }
        else
        {
            for (int j=0; j<=k; j++) {
                dp[i][j] = dp[i-1][j];
                if (j - x >= 0) {
                    // (a + b) % mod = c
                    // => c + (mod - b) = a;
                    dp[i][j] = dp[i][j] + (MOD - dp[i][j-x]);
                    dp[i][j] %= MOD;
                }
            }
        }

        cout << dp[i][k] << endl;
    }

    // for (int i=1; i<=q; i++) {
    //     for (int j=0; j<=k; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}