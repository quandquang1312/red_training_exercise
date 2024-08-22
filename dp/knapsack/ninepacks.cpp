// https://open.kattis.com/problems/ninepacks?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define int long long

// coin change dp using only once time
vector<vector<int>> fillUpDp(int n, int ttl, vector<int>& arr) {
    vector<vector<int>> dp(n + 10, vector<int>(ttl + 10, 1e9));

    dp[0][0] = 0;
    for (int i=1; i<=n; i++) {
        int val = arr[i - 1];
        for (int j=0; j<=ttl; j++) {
            dp[i][j] = dp[i-1][j];
            if (j - val >=0) {
                if (dp[i - 1][j - val] != 1e9) {
                    dp[i][j] = min(dp[i][j], dp[i-1][j - val] + 1);
                }
            }
        }
    }

    return dp;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, total_hotdog = 0, total_bun = 0;
    cin >> n;

    vector<int> hotdogs(n);
    for (int i=0; i<n; i++) {
        cin >> hotdogs[i];
        total_hotdog += hotdogs[i];
    }

    cin >> m;
    vector<int> buns(m);
    for (int i=0; i<m; i++) {
        cin >> buns[i];
        total_bun += buns[i];
    }

    vector<vector<int>> dp_h = fillUpDp(n, total_hotdog, hotdogs);
    vector<vector<int>> dp_b = fillUpDp(m, total_bun, buns);

    int ans = 1e9;
    for (int i=1; i <= total_hotdog && i<= total_bun; i++) {
        ans = min(ans, dp_h[n][i] + dp_b[m][i]);
    }

    cout << (ans == 1e9 ? "impossible" : to_string(ans)) << '\n';

    return 0;
}