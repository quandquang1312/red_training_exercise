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
    dp[1] = 1, dp[2] = 4;
    for (int i=3; i<=10; i++) {
        dp[i] += dp[i-1];
        dp[i] += dp[i-2] * 4;
        dp[i]++;
    }

    for (int i=1; i<=10; i++) {
        cout << i << ": " << dp[i] << endl;
    }
    // cout << dp[3] << endl << dp[4] << endl;

    // for (int i=3; i<=40; i++) {
        
    // }

    int tc; cin >> tc;
    while (tc--)
    {
        int n; cin >> n;


    }

    return 0;
}