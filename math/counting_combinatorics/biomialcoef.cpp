// https://cses.fi/problemset/task/1079

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int f[1000010];

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

    int tc; cin >> tc;
    f[0] = 1LL;
    f[1] = 1LL;
    for (int i=2LL; i<1000010LL; i++)
        f[i] = (f[i-1] * i) % MOD;

    while (tc--) {
        int n, k;
        cin >> n >> k;

        int ans = CnK(n, k);
        cout << ans << '\n';
    }

    return 0;
}