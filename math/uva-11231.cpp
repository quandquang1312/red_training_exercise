// https://vjudge.net/problem/UVA-11231

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

    int n, m, c;
    while ((cin >> n >> m >> c), (n || m || c))
    {
        if (n == m && n == 8) {
            cout << (c == 1) << endl;
            continue;
        }

        int c_m = (m - 8) / 2 + 1;
        int c_r = (m - 8 + 1 - c_m);
        int r_n = (n - 8) / 2 + 1;
        int r_r = (n - 8 + 1 - r_n);

        int ans = c_m * r_n + c_r * r_r;
        // cout << c_m << "-" << c_r << "," << r_n << "-" << r_r << endl;
        if (c == 1) cout << ans << endl;
        else {
            int total = (n - 8 + 1) * (m - 8 + 1);
            ans = total - ans;
            cout << ans << endl;
        }

        // if (c == 0) ans += (n - 8 + 1) / 2;

        // cout << ans << endl;
    }

    return 0;
}