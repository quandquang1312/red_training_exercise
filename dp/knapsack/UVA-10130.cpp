// https://vjudge.net/problem/UVA-10130

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define MAX_WEIGHT 35
#define MAX_N      1000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, p; cin >> n;

        vector<pair<int, int>> item(n);
        for (int i=0; i<n; i++) cin >> item[i].first >> item[i].second;

        cin >> p;
        vector<int> maxw(p);
        for (int i=0; i<p; i++) cin >> maxw[i];

        vector<vector<int>> dp(MAX_WEIGHT, vector<int>(MAX_N, false));
        int ans = 0;
        for (int j=0; j<p; j++) {
            dp.assign(MAX_WEIGHT, vector<int>(MAX_N, 0));

            int w = maxw[j];

            for (int v=0; v<=w; v++) {
                for (int i=1; i<=n; i++) {
                    auto [p_i, w_i] = item[i - 1];
                    // choose
                    if (v - w_i >= 0) dp[v][i] = max(dp[v][i], dp[v-w_i][i-1] + p_i);

                    // not choose
                    dp[v][i] = max(dp[v][i], dp[v][i-1]);
                }
            }

            ans += dp[w][n];
        }

        cout << ans << '\n';

    }

    return 0;
}