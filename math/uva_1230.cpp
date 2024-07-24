// https://vjudge.net/problem/UVA-1230

#include <bits/stdc++.h>
using namespace std;

#define int long long

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int x, y, n;
        cin >> x >> y >> n;
        int ans = binpow(x,y,n);
        cout << ans << endl;
    }

    return 0;
}