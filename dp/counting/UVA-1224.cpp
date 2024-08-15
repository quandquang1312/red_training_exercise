// https://vjudge.net/problem/UVA-1224

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int dp[35] {};
    dp[1] = 1, dp[0] = 1;

    for (int i=0; i<30; i++) {
        dp[i+1] += dp[i];
        dp[i+2] += dp[i] * 2;
    }

    for (int i=0; i<=10; i++) {
        cout << i << ": " << dp[i] << '\n';
    }

    int tc; cin >> tc;

    while (tc--) {
        int n; cin >> n;
        cout << dp[n] << '\n';
    }

    return 0;
}