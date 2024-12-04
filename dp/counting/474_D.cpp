// https://codeforces.com/contest/474/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 100010

const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr)â

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc, k; cin >> tc >> k;

    vector<int> dp(MAXN), presum(MAXN);

    for (int i=0; i<k; i++) dp[i] = 1;
    for (int i=k; i<MAXN; i++) {
        dp[i] = (dp[i-1] + dp[i-k])% MOD;
    }

    for (int i=1; i<MAXN; i++) {
        presum[i] += (presum[i-1] + dp[i]) % MOD;
    }

    for (int i=0; i<tc; i++) {
        int a, b; cin >> a >> b;
        // handle negative mod
        int ans = (presum[b] - presum[a - 1] + MOD) % MOD;
        cout << ans << "\n";
    }

    return 0;
}