// https://vjudge.net/problem/UVA-11526

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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        int start = n;
        int l = n, r = 1;
        while (start != 1) {
            int m = (l + r) >> 1;

            if (n / m < start) {
                r = m;
            } else {
                start = (n / start) + 1;
            }
        }
    }

    return 0;
}