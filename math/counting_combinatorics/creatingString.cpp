// https://cses.fi/problemset/task/1715

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    string str; cin >> str;
    int n = str.size();
    int cnt[30] {}, fact[n + 10];
    fact[0] = fact[1] = 1;

    for (int i=0; i<n; i++) cnt[str[i] - 97]++;
    for (int i=2; i<=n; i++) fact[i] = (fact[i-1] * i) % MOD;

    int ans = fact[n];
    for (int i=0; i<30; i++) {
        if (cnt[i] <= 1) continue;
        ans = (ans * binpow(fact[cnt[i]], MOD - 2)) % MOD;
    }

    cout << ans << '\n';

    return 0;
}