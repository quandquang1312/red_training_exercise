// https://www.codechef.com/problems/ROIDS?tab=statement

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1000000007;

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return res % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    map<int, int> mp;
    int x, y, maxx = n;
    for (int i=0; i<n; i++) {
        cin >> x >> y;
        mp[x]++;
        maxx = max(maxx, mp[x]);
    }

    int ans = 1;

    int f[maxx + 1];
    f[1] = 1;
    for (int i=2; i<=maxx; i++) {
        f[i] = (f[i-1] * i) % MOD;
        f[i] %= MOD;
    }

    for (auto &[k, v] : mp) {
        ans *= f[v]; // ((kf % MOD) * (invnf % MOD)) % MOD;
        ans %= MOD;
    }

    int g = __gcd(ans, f[n]);

    ans /= g;
    f[n] /= g;

    ans = (ans * binpow(f[n], MOD - 2)) % MOD;
    cout << ans << endl;

    return 0;
}