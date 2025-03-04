// https://atcoder.jp/contests/abc358/tasks/abc358_g

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 55

int dp[MAXN][MAXN];

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

    priority_queue<tuple<int, int, int, int>> q;
    q.push({0, st.first, st.second, 0});

    vector<pair<int, int>> dir {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
    auto isIn = [&] (int i, int j) {
        return i >= 1 && i <= h && j >= 1 && j <= w;
    };

    vector<vector<bool>> visited(h + 1, vector<bool>(w + 1, false));

    int ans = 0;
    while (!q.empty()) {
        auto [cost, i, j, mv] = q.top(); q.pop();
        visited[i][j] = true;

        if (mv >= k) continue;
        if (cost < dp[i][j]) continue;

        for (auto &[ii, jj] : dir) {
            int new_i = i + ii, new_j = j + jj;
            if (!isIn(new_i, new_j)) continue;

            if ((dp[new_i][new_j] < dp[i][j] + arr[new_i][new_j])) {
                dp[new_i][new_j] = dp[i][j] + arr[new_i][new_j];
                if (!visited[new_i][new_j]) q.push({dp[new_i][new_j], new_i, new_j, mv + 1});

                ans = max(ans, dp[new_i][new_j] + (k - (mv + 1)) * arr[new_i][new_j]);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}