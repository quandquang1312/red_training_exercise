// https://vjudge.net/problem/UVA-357

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 30005
#define MAXC 6

int coins[MAXC] = {0, 1, 5, 10, 25, 50};
int dp[MAXC][MAXN] {};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);

    for (int i=0; i<MAXC; i++) {
        dp[i][0] = 1;
    }

    for (int j=0; j<MAXN; j++) {
        for (int i=1; i<MAXC; i++) {
            dp[i][j] = dp[i-1][j];
            if (j - coins[i] >= 0) dp[i][j] += dp[i][j-coins[i]]; 
        }
    }

    int n = 0;
    while (cin >> n) {
        if (dp[MAXC-1][n] != 1) printf("There are %lld ways to produce %lld cents change.\n", dp[MAXC-1][n], n);
        else printf("There is only %lld way to produce %lld cents change.\n", dp[MAXC-1][n], n);
    }

    return 0;
}