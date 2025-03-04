// https://codeforces.com/contest/2069/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n + 1);
        for (int i=1; i<=n; i++) cin >> arr[i];

        vector<int> dp(4, 0);
        dp[0] = 1;

        for (int i=1; i<=n; i++) {
            int x = arr[i];

            if (x == 2) dp[x] = (dp[x] + dp[x]) % MOD; 
            dp[x] = (dp[x] + dp[x - 1]) % MOD;
        }

        cout << dp[3] << "\n";
    }

    return 0;
}