// https://vjudge.net/problem/UVA-12463

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

    int a, b, c, d, e;
    while (cin >> a >> b >> c >> d >> e) {
        if (a + b + c + d + e == 0) break;

        int ans = pow(e,2);
        ans = ans * pow(d,2);
        ans = ans * a * b * c;
        cout << ans << '\n';
    }

    return 0;
}