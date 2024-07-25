// https://atcoder.jp/contests/abc291/tasks/abc291_d

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<pair<int, int>> card(n);
    for (int i=0; i<n; i++) {
        cin >> card[i].first >> card[i].second;
    }

    vector<vector<int>> dp(n+1, vector<int>(2,0));
    dp[0][0] = 1;
    dp[0][1] = 1;

    for (int i=1; i<n; i++) {
        if (card[i].first != card[i-1].first)   dp[i][0] += dp[i-1][0];
        if (card[i].first != card[i-1].second)  dp[i][0] += dp[i-1][1];
        if (card[i].second != card[i-1].second) dp[i][1] += dp[i-1][1];
        if (card[i].second != card[i-1].first)  dp[i][1] += dp[i-1][0];

        dp[i][0] %= MOD;
        dp[i][1] %= MOD; 
    }

    cout << (dp[n-1][0] + dp[n-1][1]) % MOD << endl;

    return 0;
}