// https://codeforces.com/problemset/problem/2000/F

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int BOUND = 110;
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, k; cin >> n >> k;

        vector<vector<int>> dp(n + 1, vector<int>(BOUND, INF));
        vector<pair<int, int>> arr(n);

        int max_score = 0;
        for (int i=0; i<n; i++) {
            cin >> arr[i].first >> arr[i].second;
            max_score += arr[i].first + arr[i].second;
        }

        if (max_score < k) {
            cout << "-1\n";
            continue;
        }

        // dp[i][j]:
        //      the minimum operations to score j from with the rectangles from 0 to i-th

        dp[0][0] = 0;
        for (int i=0; i<n; i++) {
            auto [w, h] = arr[i];
            if (w > h) swap(w, h);
            for (int score=0; score<=k; score++) {
                for (int j=0; j<=(w + h); j++) {
                    if (dp[i][score] == INF || score + j >= BOUND) continue;

                    dp[i + 1][score + j] = min(dp[i + 1][score + j], dp[i][score + j]);

                    if (j <= w) dp[i + 1][score + j] = min(dp[i + 1][score + j], h * j);
                    if (j <= h) dp[i + 1][score + j] = min(dp[i + 1][score + j], w * j);

                    if (j >= (w - 1) && min(w, h) > 1) {
                        int d = j - (w - 1);
                        dp[i + 1][score + j] = min(dp[i + 1][score + j], h * (w - 1) + d);
                    }

                    if (j >= (h - 1) && ) {
                        int d = j - (h - 1);
                        dp[i + 1][score + j] = min(dp[i + 1][score + j], w * (h - 1) + d);
                    }

                    // int d = h - w;
                    // if (j >= d) {
                    //     int ret = d * w;
                    //     int new_j = j - d;
                    //     int cube = w;
                    //     while (new_j - 2 >= 0) {
                    //         ret += cube * 2 - 1;
                    //         cube--;
                    //         new_j-=2;
                    //     }
                        
                    //     if (new_j) {
                    //         ret += cube;
                    //     }

                    //     dp[i + 1][score + j] = min(dp[i + 1][score + j], ret);
                    // }

                    // if (j > 2) {
                    //     dp[i + 1][score + j] = min(dp[i + 1][score + j], (w + h - 1) + ((j - 2) * (w - 1)));
                    // }

                    // cout << score + j << ": " << dp[i + 1][score + j] << "\n";
                }
            }
        }

        int ans = INF;
        for (int j=k; j<BOUND; j++) {
            ans = min(dp[n][j], ans);
        }

        cout << ans << "\n";


    }

    return 0;
}