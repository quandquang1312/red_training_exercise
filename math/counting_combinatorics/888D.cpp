// https://codeforces.com/problemset/problem/888/D
/*

*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, MOD = 1e9 + 7, d[5], f[2000];

// Dearrengement
void precalD() {
    d[0] = 1, d[1] = 0;
    for (int i=2; i<=5; i++) {
        d[i] = ((i - 1) % MOD) * ((d[i-1] + d[i-2]) % MOD);
        d[i] %= MOD;
    }
}

void precalF() {
    f[0] = f[1] = 1;
    for (int i=2; i<2000; i++) f[i] = (f[i - 1] * i) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, k;
    cin >> n >> k;

    // Pascal Triangle
    int64_t c[n + 1][k + 1];
    memset(c, 0, sizeof c);
    for (int i = 0; i <= n; i++) { c[i][0] = 1; }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }

    precalD();
    precalF();

    int ans = 1; // The case where all a_i = i (1 2 3 ... n)
    for (int m=1; m<=k; m++) {
        // with each m from 1 to k, the case is with n - m elements are
        // in the right position
        // m elements are in the wrong position (d[m] for the number of dearrangement of size m)
        // c[n][m] for the way to choose m elements to be the dearrangement elements
        ans += d[m] * c[n][m];
    }

    cout << ans << '\n';

    return 0;
}