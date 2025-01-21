// https://codeforces.com/problemset/problem/2000/F

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n, k; cin >> n >> k;

        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        vector<pair<int, int>> arr(n);

        int maxscore = 0;
        for (int i=0; i<n; i++) {
            cin >> arr[i].first >> arr[i].second;
            maxscore += arr[i].first + arr[i].second;
        }

        if (maxscore < k) {
            cout << "-1\n";
            continue;
        }

        // dp[i][j]:
        //      the minimum operations to score j from with the rectangles from 0 to i-th

        // with a rectangle WxH
        // the cost of scoring each score increasingly is the smaller between W and H
        // in the mean time, the larger will be decrease by 1
        // cost_0 = 0 + min(w, h); if (w == min(w, h)) w--; else h--;
        // cost_1 = cost_0 + min(w, h); if (w == min(w, h)) w--; else h--;
        // cost_2 = cost_1 + min(w, h); ...
        // ...

        dp[0][0] = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<=k; j++) {
                if (dp[i][j] == INF) continue;

                int cost = 0;
                auto [w, h] = arr[i];
                maxscore = w + h;

                for (int score=0; score <= maxscore && j+score<=k; score++) {
                    dp[i + 1][j + score] = min(dp[i + 1][j + score], dp[i][j] + cost);

                    if (w >= h) {
                        w--;
                        cost += h;
                    } else {
                        h--;
                        cost += w;
                    }
                }
            }
        }

        int ans = dp[n][k];
        cout << (ans == INF ? -1 : ans) << "\n";
    }

    return 0;
}