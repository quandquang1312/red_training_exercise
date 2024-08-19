// https://dmoj.ca/problem/bbc08h

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 2000050
const int MOD = 1e9 + 7;
int f[MAXN];

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
    for (int i=2; i<MAXN; i++) f[i] = (f[i - 1] * i) % MOD;
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

    precalF();

    int n; cin >> n;

    int ans = 0;
    for (int i=0; i<=n; i++) {
        // Use hockey stick identity
        int tmp_ans = CnK(n + i + 1, i + 1);
        ans = (ans + tmp_ans) % MOD;
        // for (int j=0; j<=n; j++) {
        //     int tmp_ans = CnK(i + j, i);
        //     // cout << i << "-" << i + j << ": " << tmp_ans << '\n';
        //     ans = (ans + tmp_ans) % MOD;
        // }
    }

    cout << ans << endl;

    return 0;
}