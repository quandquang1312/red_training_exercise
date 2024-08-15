// https://vjudge.net/problem/UVA-12712

#include <bits/stdc++.h>
using namespace std;

#define MOD 10000000000007
long long f[10100];

void precalF(int r) {
    f[r] = r;
    for (int i=r-1; i >= 0; i--) f[i] = (f[i+1] * i) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++) {
        int l, mmin, mmax;
        cin >> l >> mmin >> mmax;
        long long ans = 0, n = l * l;
        precalF(n);
        for (int i=mmin; i<=mmax; i++) {
            ans = (ans + f[n - i + 1]) % MOD;
        }

        printf("Case %d: %lld\n", t, ans);
    }

    return 0;
}