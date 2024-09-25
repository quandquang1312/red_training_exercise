// https://codejam.lge.com/problem/17137

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

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

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];

        sort(arr.begin(), arr.end());
        vector<vector<int>> dp(n + 1, vector<int>(205, 0));

        for (int i=1; i<=arr[0]; i++) {
            dp[0][i] = 1;
        }

        for (int i=1; i<n; i++) {
            for (int j=1; j<=arr[i]; j++) {
                for (int k=1; k<=j; k++) {
                    // each j add to the next
                    dp[i][j] += dp[i - 1][k];
                    dp[i][j] %= MOD;
                }
            }
        }
        
        int ans = 0;
        for (int i=1; i<=arr[n-1]; i++) {
            ans += dp[n-1][i];
            ans %= MOD;
        }

        cout << (ans * n) % MOD << endl;
    }

    return 0;
}