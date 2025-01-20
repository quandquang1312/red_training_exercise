// https://codeforces.com/contest/2007/problem/A

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    /*
    10 11 12 13 14 15
    16 17 18 19 20 21
    10 11 13
    12 15 17
    14 19 21
    16 23 25

    51 52 53 54 55
    56 57 58 59 60

    51 52 53
    54 55 57
    56 59 61

    52 53 55
    54 57 59
    */

    int tc; cin >> tc;
    while (tc--) {
        int l, r; cin >> l >> r;

        int ans = 0, odd = 0, even = 0;
        for (int i=l; i<=r; i++) {
            if (i % 2) odd++;
            else even ++;
        }

        cout << min((odd / 2), even) << '\n';
    }

    return 0;
}