// https://atcoder.jp/contests/abc358/tasks/abc358_g

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 55

const int INF = 1e18;

int dp[MAXN * MAXN][MAXN][MAXN];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int h, w, k;
    cin >> h >> w >> k;

    pair<int, int> st;
    vector<vector<int>> arr(h + 1, vector<int>(w + 1));

    cin >> st.first >> st.second;

    for (int i=1; i<=h; i++) {
        for (int j=1; j<=w; j++) {
            cin >> arr[i][j];
        }
    }

    std::fill(&dp[0][0][0], &dp[MAXN * MAXN][0][0], -INF);
    dp[0][st.first][st.second] = 0;

    for (int t=1; t<=w*h; t++) {
        for (int i=1; i<=h; i++) {
            for (int j=1; j<=w; j++) {
                if (dp[t-1][i-1][j] != -INF)
                    dp[t][i][j] = max(dp[t][i][j], dp[t-1][i-1][j] + arr[i][j]);
                if (dp[t-1][i][j-1] != -INF)
                    dp[t][i][j] = max(dp[t][i][j], dp[t-1][i][j-1] + arr[i][j]);
                if (dp[t-1][i+1][j] != -INF)
                    dp[t][i][j] = max(dp[t][i][j], dp[t-1][i+1][j] + arr[i][j]);
                if (dp[t-1][i][j+1] != -INF)
                    dp[t][i][j] = max(dp[t][i][j], dp[t-1][i][j+1] + arr[i][j]);
            }
        }
    }

    int ans = 0;
    for (int t=0; t<=min(k, h*w); t++) {
        for (int i=1; i<=h; i++) {
            for (int j=1; j<=w; j++) {
                if (dp[t][i][j] >= 0)
                    ans = max(ans, dp[t][i][j] + (k - t) * arr[i][j]);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}