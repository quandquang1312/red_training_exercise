// https://cses.fi/problemset/task/1095

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;

int binpow(int a, int b, int mod) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }

    return res;
}

int solve(int a, int b) {
    int amodm = a % MOD;
    int powb  = binpow(amodm, b, MOD);

    return powb;
}

int32_t main() {
    int tc; cin >> tc;
    while (tc--) {
        int a, b; cin >> a >> b;

        if (a == 0 && b == 0) {
            cout << "1\n";
            continue;
        }

        int ans = solve(a, b);
        cout << ans << endl;
    }
    return 0;
}