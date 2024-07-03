// https://open.kattis.com/problems/cokolada

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int k; cin >> k;

    if ((int) __builtin_popcount(k) == 1) {
        cout << k << " " << 0 << endl;
        return 0;
    }

    int last_bit = -1, first_bit = -1;
    for (int i=21; i>=0; i--) {
        if (k & (1 << i) && last_bit == -1)
            last_bit = i;
        if (k & (1 << i)) first_bit = i;
    }

    int ans = (1 << last_bit) << 1;
    int cnt = last_bit - first_bit + 1;

    cout << ans << " " << cnt << endl;
    return 0;
}