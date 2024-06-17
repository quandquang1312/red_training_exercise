// https://codeforces.com/problemset/problem/118/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e8;

int n1, n2, k1, k2;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n1 >> n2 >> k1 >> k2;

    int dp[n1+1][n2+1][2];
    memset(dp, 0, sizeof dp);

    for (int i=0; i<n1; i++) dp[i][0][0] = 1;
    for (int i=0; i<n2; i++) dp[0][i][1] = 1;

    for (int i=0; i<=n1; i++) {
        for (int j=0; j<=n2; j++) {
            for (int k=1; k <= k1 && k + j <= n2; k++) {
                dp[i][j+][1] = 
            }
        }
    }

    return 0;
}