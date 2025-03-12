// https://codejam.lge.com/problem/29892

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 505

const int INF = 1e18;

int dp[MAXN][MAXN][3];
int presum[MAXN][MAXN][2][3];
int cnt[MAXN][MAXN][3];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;

    vector<vector<char>> grid(n + 1, vector<char>(m + 1));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '1') presum[i][j][0][1] = i, presum[i][j][1][1] = j, cnt[i][j][1] = 1;
            if (grid[i][j] == '2') presum[i][j][0][2] = i, presum[i][j][1][2] = j, cnt[i][j][2] = 1;

            for (int d=1; d<=2; d++) {
                presum[i][j][0][d] += presum[i-1][j][0][d] + presum[i][j-1][0][d] - presum[i-1][j-1][0][d];
                presum[i][j][1][d] += presum[i-1][j][1][d] + presum[i][j-1][1][d] - presum[i-1][j-1][1][d];
                cnt[i][j][d] += cnt[i-1][j][d] + cnt[i][j-1][d] - cnt[i-1][j-1][d];
            }
        }
    }

    auto query = [] (int from_row, int from_col, int to_row, int to_col, int d) -> pair<int, int> {
        int rs_1 = presum[to_row][to_col][0][d] - presum[from_row - 1][to_col][0][d]
                - presum[to_row][from_col - 1][0][d] + presum[from_row - 1][from_col - 1][0][d];

        int rs_2 = presum[to_row][to_col][1][d] - presum[from_row - 1][to_col][1][d]
                - presum[to_row][from_col - 1][1][d] + presum[from_row - 1][from_col - 1][1][d]; 

        return {rs_1, rs_2};
    };

    auto getCnt = [] (int from_row, int from_col, int to_row, int to_col, int d) -> int {
        int rs = cnt[to_row][to_col][d] - cnt[from_row - 1][to_col][d]
                - cnt[to_row][from_col - 1][d] + cnt[from_row - 1][from_col - 1][d];

        return rs;
    };

    int rm = k/2, ans = INF;
    for (int i=1 + rm; i<=n - rm; i++) {
        for (int j=1 + rm; j<=m - rm; j++) {
            int top  = max(1LL, i - rm), bot   = min(n, i + rm);
            int left = max(1LL, j - rm), right = min(m, j + rm);

            int from_row, from_col, to_row, to_col;
            for (int d=1; d<=2; d++) {
                auto [x1, y1] = query(top, left, i, j, d);
                int cur_cnt = getCnt(top, left, i, j, d);

                dp[i][j][d] += abs((i * cur_cnt) - x1);
                dp[i][j][d] += abs((j * cur_cnt) - y1);

                auto [x2, y2] = query(i+1, left, bot, j, d);
                cur_cnt = getCnt(i+1, left, bot, j, d);

                dp[i][j][d] += abs((i * cur_cnt) - x2);
                dp[i][j][d] += abs((j * cur_cnt) - y2);

                auto [x3, y3] = query(top, j+1, i, right, d);
                cur_cnt = getCnt(top, j+1, i, right, d);

                dp[i][j][d] += abs((i * cur_cnt) - x3);
                dp[i][j][d] += abs((j * cur_cnt) - y3);

                auto [x4, y4] = query(i+1, j+1, bot, right, d);
                cur_cnt = getCnt(i+1, j+1, bot, right, d);

                dp[i][j][d] += abs((i * cur_cnt) - x4);
                dp[i][j][d] += abs((j * cur_cnt) - y4);
            }

            ans = min(ans, abs(dp[i][j][1] - dp[i][j][2]));
        }
    }

    cout << ans << "\n";

    return 0;
}