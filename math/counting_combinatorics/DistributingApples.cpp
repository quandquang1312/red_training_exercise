// https://cses.fi/problemset/task/1716

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int f[2000010];

void calculateF(int n, int m) {
    f[0] = f[1] = 1;
    for (int i=2; i<=(n + m + 5); i++) f[i] = (f[i - 1] * i) % MOD;
}

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

int inv(int n) {
    return binpow(n, MOD - 2LL);
}

int CnK(int n, int k) {
    if (n == k) return 1LL;
    if (n < k) return 0LL;

    return ((f[n] * inv(f[k]) % MOD) * (inv(f[n-k])) % MOD) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    calculateF(n, m);
    int ans = CnK(m + n - 1, n - 1);
    cout << ans << '\n';

    return 0;
}
