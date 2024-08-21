// https://open.kattis.com/problems/knapsack?tab=metadata

#include <bits/stdc++.h>
using namespace std;

pair<int, int> arr[2025];
int dp[2025][2025];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int c, n;
    while (cin >> c >> n) {
        memset(dp, 0, sizeof dp);
        for (int i=0; i<n; i++) cin >> arr[i].first >> arr[i].second;

        for (int sm=0; sm<=c; sm++) {
            for (int i=1; i<=n; i++) {
                auto [v_i, w_i] = arr[i - 1];
                if (sm - w_i >= 0) dp[sm][i] = max(dp[sm - w_i][i - 1] + v_i, dp[sm][i]);
                dp[sm][i] = max(dp[sm][i], dp[sm][i - 1]);
            }
        }

        int res = dp[c][n], sm = c;

        // Trace solution knapsack value
        vector<int> ans;
        for (int i=n; i >= 0 && res > 0; i--) {
            if (res != dp[sm][i - 1]) {
                ans.push_back(i - 1);
                res -= arr[i - 1].first;
                sm  -= arr[i - 1].second;
            }
        }

        cout << ans.size() << '\n';
        for (auto &e : ans)
            cout << e << ' ';
        cout << '\n';
    }

    return 0;
}