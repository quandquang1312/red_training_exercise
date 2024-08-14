// https://codejam.lge.com/problem/27371

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;
int f[200010];

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

void precalF() {
    f[0] = f[1] = 1;
    for (int i=2; i<200010; i++) f[i] = (f[i - 1] * i) % MOD;
}

int CnK(int n, int k) {
    if (n < 0 || k < 0) return 0LL;
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

    precalF();

    while (tc--) {
        int n, m;
        cin >> n >> m;

        // n.o ways to place k = 0 to n-1 X between 0 -> n-th O (n holes)
        // the remain X is m - k
        // n.o ways to place m - k X between n-th -> m-th X (m - n holes)
        int ans = 0;
        for (int k=0; k<=n-1; k++) {
            int fi = CnK(n + k - 1, k);
            int remain = m - k - 1;
            int a1 = remain - 1, ap = remain + (m - n) - 1;
            int p = ap - a1 + 1;

            cout << k << " rm: " << remain << '\n';
            cout << k << ": " << a1 << "-" << ap << "-" << p << '\n';

            int upp = binpow(f[a1], p) * (f[ap] / f[a1]);
            int low = binpow(f[remain], p) * f[p] * f[ap - p + 1 - remain];

            cout << k << ": " << upp << " <-> " << low << '\n';

            for (int holes = 0; holes <= m - n; holes++) {
                // int holes = m - n;
                int se = CnK(remain + holes - 1, remain);
                ans = (ans + ((fi % MOD) * (se % MOD)) % MOD) % MOD;
                // cout << k << ": " << fi << " <-> " << se << '\n';
            }
        }

        cout << ans << '\n';
    }

    return 0;
}