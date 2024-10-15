// https://atcoder.jp/contests/abc375/tasks/abc375_e

#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

int dp[105][505][505];
int T[105], W[105], S, n;

int solve(int idx, int A, int B) {
    if (idx >= n) {
        if (A == B && (A * 3 == S)) return 0;
        return INF;
    }
    
    // if (A * 3 > S || B * 3 > S || (S - A - B) * 3 > S) return INF;
    
    if (dp[idx][A][B] != -1) return dp[idx][A][B];

    int ans = INF;
    
    ans = min(ans, (T[idx] != 1) + solve(idx + 1, A + W[idx], B));
    ans = min(ans, (T[idx] != 2) + solve(idx + 1, A, B + W[idx]));
    ans = min(ans, (T[idx] != 3) + solve(idx + 1, A, B));
    
    return dp[idx][A][B] = ans;
}

int bottomup() {
    for (int i=0; i<=n; i++)
        for (int j=0; j<505; j++)
            for (int k=0; k<505; k++)
                dp[i][j][k] = INF;

    dp[0][0][0] = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<=S/3; j++) {
            for (int k=0; k<=S/3; k++) {
                if (dp[i][j][k] != INF) {
                    // t1
                    if (j+W[i]<505) dp[i+1][j+W[i]][k] = min(dp[i+1][j+W[i]][k], (T[i] != 1) + dp[i][j][k]);
                    // t2
                    if (k+W[i]<505) dp[i+1][j][k+W[i]] = min(dp[i+1][j][k+W[i]], (T[i] != 2) + dp[i][j][k]);
                    // t3
                    dp[i+1][j][k] = min(dp[i+1][j][k], (T[i] != 3) + dp[i][j][k]);
                }
            }
        }
    }

    return dp[n][S/3][S/3];
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n;
    
    // memset(dp, -1, sizeof dp);
    
    for (int i=0; i<n; i++) {
        cin >> T[i] >> W[i];
        S += W[i];
    }
    
    if (S % 3) {
        cout << "-1" << "\n";
        return 0;
    }

    int ans_2 = bottomup();
    cout << (ans_2 >= INF ? -1 : ans_2) << "\n";

    return 0;
}