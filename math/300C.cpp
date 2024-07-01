// https://codeforces.com/problemset/problem/300/C

#include <bits/stdc++.h>
using namespace std;

#define int int64_t
const int mod = 1000000007;

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }

    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int a, b, n;
    cin >> a >> b >> n;

    

    auto checkGood = [](int a, int b, int numb) -> bool {
        while (numb) {
            if ((numb % 10 != a && numb % 10 != b))
                return false;
            numb /= 10;
        }

        return true;
    };

    int f[n+1] {};
    f[0] = 1;

    for (int i=1; i<=n; i++) f[i] = (f[i-1] * i) % mod;

    int ans = 0;
    for (int numbA=0; numbA<=n; numbA++) {
        int sm = numbA * a + (n - numbA) * b;
        if (checkGood(a, b, sm)) {
            int fn = (f[n-numbA] % mod * f[numbA] % mod) % mod;
            int inv = binpow(fn, mod - 2);
            ans += ((f[n] % mod * inv % mod) % mod);
        }
    }

    cout << ans << endl;


    return 0;
}