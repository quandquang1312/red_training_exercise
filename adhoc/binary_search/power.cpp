// https://vjudge.net/contest/687521#problem/A

#include <bits/stdc++.h>
using namespace std;

#define int long long

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a);
        a = a * a;
        b >>= 1;
    }

    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    auto check = [&] (int k, int l, int r) -> bool {
        if (k == 1) return true;
        for (int x=1;; x++) {
            int xk = binpow(x, k);
            if (xk > r) return false;
            if (xk >= l && xk <= r) return true;
        }

        return false;
    };

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++) {
        int l, r; cin >> l >> r;

        int ans = 1;
        for (int k=64; k>=1 && ans == 1; k--) {
            if (check(k, l, r)) ans = k;
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}