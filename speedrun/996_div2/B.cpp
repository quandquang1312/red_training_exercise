// https://codeforces.com/contest/2055/problem/A

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

        vector<int> a(n), b(n);

        int cnt = 0, j = -1;
        for (int i=0; i<n; i++) cin >> a[i];
        for (int i=0; i<n; i++) {
            cin >> b[i];
            if (b[i] > a[i]) {
                cnt++;
                j = i;
            }
        }

        if (cnt == 0) cout << "YES\n";
        else if (cnt >= 2) cout << "NO\n";
        else {
            int mmin = 1e9;
            for (int i=0; i<n; i++) {
                if (i == j) continue;
                mmin = min(mmin, a[i] - b[i]);
            }

            if (b[j] - a[j] <= mmin) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}