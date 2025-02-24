// https://codeforces.com/contest/2064/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 3e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n + 1);
        for (int i=1; i<=n; i++) cin >> arr[i];

        vector<int> dp_f(n + 1, 0), dp_b(n + 2, 0);

        for (int i=1; i<=n; i++) {
            if (arr[i] > 0) {
                dp_f[i] = dp_f[i - 1] + arr[i]; 
            } else {
                dp_f[i] = dp_f[i]; 
            }
        }

        for (int i=n; i>=1; i--) {
            if (arr[i] < 0) {
                dp_b[i] = dp_b[i + 1] + abs(arr[i]); 
            } else {
                dp_b[i] = dp_b[i + 1];
            }
        }

        int ans = 0;
        for (int i=1; i<=n; i++) {
            ans = max(ans, dp_f[i] + dp_b[i]);
            cout << i << ": " << dp_f[i] << "-" << dp_b[i] << "\n";
        }

        cout << ans << "\n";
    }

    return 0;
}