// https://vjudge.net/contest/678673#problem/C

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

    int n; cin >> n;

    int ans = 1;
    while (n != 1) {
        if (__builtin_popcount(n) == 1) {
            ans += __builtin_ctz(n);
            break;
        }

        if (n % 2 == 0) n /= 2;
        else n = n * 3 + 1;
        ans++;
    }

    cout << ans << "\n";

    return 0;
}