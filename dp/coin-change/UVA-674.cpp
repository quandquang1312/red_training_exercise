// https://vjudge.net/problem/UVA-674

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 7500

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    vector<int> dp(MAXN, 0);
    vector<int> coins {1, 5, 10, 25, 50};

    dp[0] = 1;
    for (auto &coin : coins) {
        for (int i=0; i<MAXN; i++) {
            if (i - coin >= 0) dp[i] += dp[i-coin];
        }
    }

    int n;
    while (cin >> n) {
        cout << dp[n] << '\n';
    }

    return 0;
}