// https://vjudge.net/problem/UVA-11310

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> ans;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int dp[55] {};
    dp[0] = 1;

    for (int i=0; i<=40; i++) {
        dp[i + 1] += dp[i];
        dp[i + 2] += dp[i] * 4;
        dp[i + 3] += dp[i] * 2;
    }

    int tc; cin >> tc;
    while (tc--)
    {
        int n; cin >> n;
        cout << dp[n] << "\n";
    }

    return 0;
}