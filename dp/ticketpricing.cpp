// https://open.kattis.com/problems/ticketpricing

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, w, prices[52+1][102], seats[52+1][102], dp[52+1][500];
int numb[52+1], trace = -1;

int solve(int idx, int left) {
    if (idx > w+1) return 0;

    if (dp[idx][left] != -1) return dp[idx][left];

    int ans = 0;
    for (int j=0; j<numb[idx]; j++) {
        int max_sale = min(left, seats[idx][j]);
        if (left < seats[idx][j]) {
            ans = max(ans, max_sale * prices[idx][j]);
            continue;
        }
        if (idx == 0) {
            if (ans == solve(idx+1, left - max_sale) + prices[idx][j] * max_sale) {
                if (prices[idx][j] < prices[idx][trace]) trace = j;
            } else if ((solve(idx+1, left-max_sale) + prices[idx][j] * max_sale) > ans) {
                trace = j;
            }
        }

        ans = max(ans, solve(idx+1, left - max_sale) + prices[idx][j] * max_sale);
    }

    return dp[idx][left] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n >> w;

    for (int i=0; i<=w; i++) {
        cin >> numb[i];
        for (int j=0; j<numb[i]; j++) cin >> prices[i][j];
        for (int j=0; j<numb[i]; j++) cin >> seats[i][j];
    }

    memset(dp, -1, sizeof dp);

    // for (int j=0; j<numb[0]; j++) {
    //     int max_sale = min(n, seats[0][j]);
    //     dp[1][n-max_sale] = max(dp[1][n-max_sale], prices[0][j] * max_sale);
    // }

    // for (int i=1; i<=w; i++) {
    //     for (int j=0; j<numb[i]; j++) {
    //         for (int k=0; k<=n; k++) {
    //             if (dp[i][k] != -1) {
    //                 int max_sale = min(k, seats[i][j]);
    //                 dp[i+1][k-max_sale] = max(dp[i+1][k-max_sale], dp[i][k] + prices[i][j] * max_sale);
    //             }
    //         }
    //     }
    // }

    cout << solve(0, n) << endl;;

    // int ans = -1;
    // for (int i=0; i<=n; i++) {
    //     ans = max(ans, dp[w+1][i]);
    // }

    // cout << ans << endl;
    cout << prices[0][trace] << endl;

    return 0;
}