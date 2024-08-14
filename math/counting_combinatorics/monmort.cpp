// https://judge.yosupo.jp/problem/montmort_number_mod

#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, MOD = 1e9 + 7, dp[1000100];

// Dearrangement
void precal() {
    dp[0] = 1, dp[1] = 0;
    for (int i=2; i<=n; i++) {
        dp[i] = ((i - 1) % MOD) * ((dp[i-1] + dp[i-2]) % MOD);
        dp[i] %= MOD;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> MOD;
    precal();

    for (int i=1; i<=n; i++) {
        cout << dp[i] << " ";
    }

    return 0;
}