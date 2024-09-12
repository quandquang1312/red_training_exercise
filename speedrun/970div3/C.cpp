// https://codeforces.com/contest/2008/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

int check(int n) {
    return (n * (n + 1)) / 2;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int l, r;
        cin >> l >> r;

        int lim = r - l;
        int lo = 1, hi = 1e9;
        while (lo < hi) {
            int m = (lo + hi + 1) >> 1;
            if (check(m) >= lim) hi = m - 1;
            else lo = m;
        }

        cout << lo << '\n';
    }

    return 0;
}