// https://atcoder.jp/contests/abc365/tasks/abc365_d

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
    string str; cin >> str;
    str = '0' + str;
    
    // 0 for R
    // 1 for P
    // 2 for S
    int dp[n+1][3];
    memset(dp, 0, sizeof dp);

    int mtw, mtl;

    for (int i=1; i<=n; i++) {
        mtw = (str[i] == 'R' ? 1 : (str[i] == 'P' ? 2 : 0));
        mtl = (str[i] == 'R' ? 2 : (str[i] == 'P' ? 0 : 1));
        dp[i][0] = max(dp[i-1][1], dp[i-1][2]) + (mtw == 0);
        dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + (mtw == 1);
        dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + (mtw == 2);
        dp[i][mtl] = 0;
    }

    int ans = max(dp[n][0], max(dp[n][1], dp[n][2]));

    cout << ans << '\n';

    return 0;
}