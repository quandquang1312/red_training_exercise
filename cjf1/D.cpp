#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--)
    {
        int r, c, n, st;
        cin  >> r >> c >> n >> st;

        bool obst_ch[r+1][c+1];

        for (int i=0; i<=r; i++) {
            for (int j=0; j<=c; j++) {
                obst_ch[i][j] = false;
            }
        }

        vector<pair<int, int>> obs(n);
        vector<vector<pair<int, int>>> seg(c+1); 

        for (int i=0; i<n; i++) {
            cin >> obs[i].first >> obs[i].second;
            obst_ch[obs[i].first][obs[i].second] = true;
        }

        sort(obs.begin(), obs.end(), [](pair<int, int> p1, pair<int, int> p2) {
            if (p1.second == p2.second) return p1.first < p2.first;
            return p1.second < p2.second;
        });

        int lst[c+1];
        for (int i=0; i<=c; i++) { lst[i] = 1; }

        for (auto &e : obs) {
            int col = e.second, row = e.first;
            // cout << col << "-" << row << endl;
            // cout << lst[col] << ":" << row-1 << endl;
            seg[col].push_back({lst[col], row - 1});
            lst[col] = row + 1;
        }

        // for (int i=1; i<=c; i++) {
        //     cout << i << "-" << seg[i].size() << ": ";
        //     for (int j=0; j<seg[i].size(); j++) {
        //         cout << "{" << seg[i][j].first << "," << seg[i][j].second << "},";
        //     }
        //     cout << endl;
        // }

        int dp[r+5][c+5];
        memset(dp, 0, sizeof dp);

        int col1_valid = -1, first_r = 1, last_r = r;
        for (int i=0; i<seg[1].size(); i++) {
            if (seg[1][i].first <= st && st <= seg[1][i].second) {
                col1_valid = seg[1][i].second - seg[1][i].first;
                first_r = seg[1][i].first, last_r = seg[1][i].second;
                break;
            }
        }

        // cout << first_r << ": " << last_r << endl;

        for (int i=1; i<=r; i++) {
            dp[i][1] = last_r - first_r - abs(st - i) + 1;
            // cout << dp[i][1] << "\n";
        }

        for (int j=2; j<=c+1; j++) {
            for (int i=1; i<=r; i++) {
                if (obst_ch[i][j] || obst_ch[i][j-1]) continue;
                int ans_d = 1LL;
                if (j == 2) {
                    dp[i][j] = dp[i][j-1];
                    continue;
                }

                if (dp[i][j-1] == 0) {
                    dp[i][j] = dp[i-1][j-1] + dp[i+1][j-1];
                    continue;
                }

                // check if the dp[i][j-1] is in which segment?
                for (int k=0; k<seg[j-1].size(); k++) {

                    // it's in the segment k
                    if (i >= seg[j-1][k].first && i <= seg[j-1][k].second) {
                        for (int d=seg[j-1][k].first; d<=seg[j-1][k].second; d++) {
                            // above
                            int length = seg[j-1][k].second - seg[j-1][k].first + 1;
                            int sm_d = dp[d][j-1] * length - abs(d - (i - 1));

                            // below
                            ans_d += sm_d;
                        }

                        break;
                    }
                }

                dp[i][j] += max(1LL, ans_d);
            }
        }

        for (int i=1; i<=r; i++) {
            for (int j=1; j<=c+1; j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
            // cout << dp[r][c] << " ";
        }
        cout << endl;
    }

    return 0;
}