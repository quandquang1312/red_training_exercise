// https://codeforces.com/contest/2007/problem/B

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200010

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        unordered_map<int, int> mp;
        int ans = -1;
        for (int i=1, x; i<=n; i++) {
            cin >> x;
            mp[x] = 1;
            ans = max(x, ans);
        }

        for (int i=0; i<m; i++) {
            char c;
            int l, r;
            cin >> c >> l >> r;
            if (c == '+') {
                if (l <= ans && r >= ans) ans++;
            } else {
                if (l <= ans && r >= ans) ans--;
            }

            cout << ans << " ";
        }

        cout << '\n';
    }

    return 0;
}