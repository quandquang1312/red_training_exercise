// https://vjudge.net/problem/UVA-12955

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e9
const int MAXN = 2*1e4+5;

int factorial[9];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    factorial[1] = 1;

    for (int i=2; i<=8; i++) {
        factorial[i] = i * factorial[i-1];
    }

    int dp[MAXN+1][9];

    for (int i=0; i<=MAXN; i++)
        for (int j=0; j<=8; j++) dp[i][j] = INF;

    for (int j=0; j<=8; j++) dp[0][j] = 0;

    for (int i=1; i<=MAXN; i++) {
        for (int j=1; j<=8; j++) {
            dp[i][j] = dp[i][j-1];
            if (factorial[j] == i) dp[i][j] = 1;
            else {
                if (i - factorial[j] >= 0) dp[i][j] = min(dp[i][j], dp[i - factorial[j]][j-1] + 1);
                if (i - factorial[j] >= 0) dp[i][j] = min(dp[i][j], dp[i - factorial[j]][j] + 1);
            }
        }
    }

    int n = 1;
    while (cin >> n)
    {
        cout << (dp[n][8]) << endl;
    }

    return 0;
}