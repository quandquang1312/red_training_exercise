//

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int cal_i(int n) {
    int i = (n * (n + 1)) % MOD;
    i = (i * binpow(2, MOD - 2));
    return i;
}

int cal_i2(int n) {
    int i2 = (n * (n + 1)) % MOD;
    i2 = (i2 * ((2 * n) % MOD + 1) % MOD) % MOD;
    i2 = (i2 * binpow(6, MOD - 2));
    return i2;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int t; cin >> t;

    while (t--) {
        int n; cin >> n;

        int i2 = (2 * cal_i2(n - 1)) % MOD;
        // cout << n << " - i2: " << i2 << "\n";
        int ans = cal_i(n - 1);
        // cout << n << " - ans: " << ans << "\n";

        ans = (ans + i2) % MOD;
        ans = (ans + (n * n) % MOD) % MOD;
        // cout << n << ": " << ans << "\n";
        ans = (2022 * ans) % MOD;

        cout << ans << "\n";
    }

    return 0;
}