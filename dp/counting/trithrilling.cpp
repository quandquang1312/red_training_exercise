// https://open.kattis.com/problems/tritiling?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 30

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    vector<int> dp(MAXN + 1, 0);
    dp[0] = 1;

    for (int i=0; i<=MAXN; i+=2) {
        dp[i + 2] += dp[i] * 3;
        for (int j=i+4; j<=MAXN; j+=2)
            dp[j] += dp[i] * 2;
    }

    int n;
    while (cin >> n) {
        if (n == -1) break;

        cout << dp[n] << '\n';
    }

    return 0;
}