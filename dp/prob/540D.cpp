// https://codeforces.com/contest/540/problem/D

#include <bits/stdc++.h>
using namespace std;

#define MAXN 105

double dp[MAXN][MAXN][MAXN];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int r, s, p;
    cin >> r >> s >> p;

    dp[r][s][p] = 1.0;
    for (int i=r; i>=0; i--) {
        for (int j=s; j>=0; j--) {
            for (int k=p; k>=0; k--) {
                if (i == 0 && j == 0) continue;
                if (i == 0 && k == 0) continue;
                if (k == 0 && j == 0) continue;
                if (dp[i][j][k] == 0.0) continue;

                int wayR = i * k;
                int wayS = j * i;
                int wayP = k * j;

                int T = (wayR + wayS + wayP);

                if (i > 0) dp[i-1][j][k] += dp[i][j][k] * (wayR * 1.0 / T);
                if (j > 0) dp[i][j-1][k] += dp[i][j][k] * (wayS * 1.0 / T);
                if (k > 0) dp[i][j][k-1] += dp[i][j][k] * (wayP * 1.0 / T);
            }
        }
    }

    double ans_r = 0.0, ans_s = 0.0, ans_p = 0.0;
    for (int i=1; i<=r; i++) ans_r += dp[i][0][0];
    for (int i=1; i<=s; i++) ans_s += dp[0][i][0];
    for (int i=1; i<=p; i++) ans_p += dp[0][0][i];

    printf("%.12f %.12f %.12f\n", ans_r, ans_s, ans_p);

    return 0;
}