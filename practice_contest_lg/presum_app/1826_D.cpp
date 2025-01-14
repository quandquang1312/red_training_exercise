// https://codeforces.com/problemset/problem/1826/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n + 1), ap(n + 1), am(n + 1);
        for (int i=1; i<=n; i++) {
            cin >> a[i];
            ap[i] = a[i] + i;
            am[i] = a[i] - i;
        }

        vector<int> max_ap(n + 5, -INF), max_am(n + 5, -INF);
        for (int i=1; i<=n; i++) max_ap[i] = max(max_ap[i - 1], ap[i]);
        for (int i=n; i>=1; i--) max_am[i] = max(max_am[i + 1], am[i]);

        int ans = -INF;
        for (int i=2; i<n; i++) {
            ans = max(ans, a[i] + max_ap[i - 1] + max_am[i + 1]);
        }

        cout << ans << "\n";
    }

    return 0;
}