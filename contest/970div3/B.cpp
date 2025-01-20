// https://codeforces.com/contest/2008/problem/B

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    auto checkSide = [](int r, int c, int x) -> bool {
        int n = r * c;
        if (x < c) return true;
        if (x >= n - c) return true;
        if (x % c == 0) return true;
        if ((x + 1) % c == 0) return true;

        return false;
    };

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        string str; cin >> str;

        int sq = sqrt(n);
        if (sq * sq != n) {
            cout << "No\n";
            continue;
        }

        int r = sq, c = sq;

        bool ans = true;

        for (int i=0; i<n && ans; i++) {
            if (checkSide(r, c, i)) {
                if (str[i] == '0') ans = false;
            } else {
                if (str[i] == '1') ans = false;
            }
        }

        cout << (ans ? "Yes\n" : "No\n");

    }

    return 0;
}