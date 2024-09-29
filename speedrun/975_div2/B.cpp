// https://codeforces.com/contest/2019/problem/B

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

    int tc; cin >> tc;
    while (tc--) {
        int n, q; cin >> n >> q;
        vector<int> arr(n + 1);
        for (int i=1; i<=n; i++) cin >> arr[i];

        vector<int> dp(n + 1);
        for (int i=1; i<=n/2; i++) {
            if (i == 1) {
                dp[i] = (n - i);
            } else {
                dp[i] = dp[i-1] + i - 1;
            }
        }

        for (int i=n; i>n/2; i--) {
            dp[i] = dp[n - i];
        }

        for (int i=1; i<n; i++) {
            cout << arr[i] << " - " << arr[i + 1] << ": " << dp[i] << "\n";
        }

        for (int i=0, x; i<q; i++) {
            cin >> x;
        }
    }

    return 0;
}