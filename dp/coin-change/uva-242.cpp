// https://vjudge.net/problem/UVA-242

#include <bits/stdc++.h>
using namespace std;

pair<int, int> fillUpDp(vector<int>& arr, int s) {
    int n = arr.size();

    int max_e = *max_element(arr.begin(), arr.end());
    int upp   = max_e * s + 10;

    vector<vector<int>> dp(n + 1, vector<int>(upp, 1e9));
    dp[0][0] = 0;

    int j=0;
    for (; j<upp; j++) {
        for (int i=1; i<=n; i++) {
            int val = arr[i - 1];
            dp[i][j] = min(dp[i][j], dp[i-1][j]);
            if (j - val >= 0) dp[i][j] = min(dp[i][j-val] + 1, dp[i][j]);
        }

        if (dp[n][j] > s) {
            j -= 1;
            break;
        }
    }

    return {j, arr.size()};
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int s;
    while (cin >> s) {
        if (s == 0) break;

        int n; cin >> n;

        int max_do[n];
        vector<vector<int>> stamps(n);
        for (int i=0, sz; i<n; i++) {
            cin >> sz;
            stamps[i].resize(sz);
            max_do[i] = 0;
            for (int j=0; j<sz; j++) {
                cin >> stamps[i][j];
                max_do[i] = max(max_do[i], stamps[i][j]);
            }
        }

        for (auto &e : stamps) {
            sort(e.begin(), e.end());
        }

        sort(stamps.begin(), stamps.end(), [](vector<int> v1, vector<int> v2) {
            if (v1.size() != v2.size()) {
                return v1.size() < v2.size();
            }
            int n = v1.size() - 1;
            for (int i=n; i>=0; i--) {
                if (v1[i] == v2[i]) continue;
                return v1[i] < v2[i];
            }

            return v1[0] < v2[0];
        });

        int ans = -1;
        vector<int> trace;
        for (int i=0; i<stamps.size(); i++) {
            vector<int> arr = stamps[i];
            auto [mx, sz] = fillUpDp(arr, s);
            if (mx > ans) {
                trace = {i};
                ans = mx;
            }
        }

        printf("max coverage =%4d :", ans);
        for (auto &e : stamps[trace[0]]) {
            printf("%3d", e);
        }
        puts("");
    }

    return 0;
}