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
        // n.o ways to place the remain Os between n-th -> m-th X (m - k holes)
        int ans = 0;
        for (int k=0; k<=n-1; k++) {
            int fi = CnK(n + k - 1, k);
            int rm_A = m - n - 1;
            int hole = m - k; // remain B + 1
            int se = CnK(hole + rm_A, rm_A);
            ans = (ans + (fi * se) % MOD) % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}