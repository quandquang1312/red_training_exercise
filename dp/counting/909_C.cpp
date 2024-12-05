// https://codeforces.com/contest/909/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 5005

const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<char> s(n);
    for (auto &c : s) cin >> c;

    // for (int i=0; i<n; i++) cout << s[i];
    // cout << "\n";

    vector<vector<int>> dp(n + 1, vector<int>(MAXN, 0));
    dp[0][0] = 1; // first line with level 0 is 1

    for (int i=1; i<n; i++) {
        if (s[i-1] == 's') {
            vector<int> cnt_lvl;
            int sm_lvl = 0;
            for (int j=0; j<n; j++) {
                if (dp[i-1][j] != 0) {
                    cnt_lvl.push_back(dp[i-1][j]);
                    sm_lvl += dp[i-1][j];
                }
            }

            int idx = 0;
            for (int j=0; j<=i; j++) {
                dp[i][j] += sm_lvl;
                dp[i][j] %= MOD;
                if (dp[i-1][j] != 0) {
                    sm_lvl -= cnt_lvl[idx];
                    idx++;
                }
            }
        } else { // 'f'
            vector<int> cnt_lvl;
            for (int j=0; j<n; j++) {
                if (dp[i-1][j] != 0) cnt_lvl.push_back(dp[i-1][j]);
            }

            for (int j=1; j<n; j++) {
                dp[i][j] += dp[i-1][j-1];
                dp[i][j] %= MOD;
            }
        }
    }

    int ans = 0;
    for (int i=0; i<n; i++) {
        ans += dp[n-1][i];
        ans %= MOD;
    }

    cout << ans << "\n";

    return 0;
}