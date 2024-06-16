// https://codejam.lge.com/problem/27360

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 510
#define MAXC 12

const int MOD = 1e9 + 7;

vector<vector<vector<int>>> ans;
char grid[MAXN][MAXC];
int r, c, k, dp[MAXN][1 << MAXC];

void findPer(char s[], int idx, vector<int> cur, int numbSwitch, int row)
{
    if (idx >= c) {
        if (cur.size() == numbSwitch) ans[row].push_back(cur);
        return;
    }

    // skip
    findPer(s, idx+1, cur, numbSwitch, row);

    // set a switch
    if ((idx <= c - 1) && (s[idx] == '-') && (s[idx+1] == '-')) {
        cur.push_back(idx);
        findPer(s, idx+2, cur, numbSwitch, row);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;

    while (tc--) {

        cin >> r >> c >> k;
        string str; cin >> str;

        ans.clear();
        for (int i=1; i<=r; i++) {
            for (int j=1; j<=c; j++) {
                grid[i][j] = '-';
            }
        }
        memset(dp, -1, sizeof dp);

        int row, col;
        for (int i=0; i<k; i++) {
            cin >> row >> col;
            grid[row][col] = '+';
        }

        ans.resize(r+1);
        for (int i=1; i<=r; i++) {
            vector<int> cur;
            for (int j=5; j>=1; j--)
                findPer(grid[i], 1, cur, j, i);
        }

        int init_mask = (1 << c) - 1;

        memset(dp, 0, sizeof dp);

        dp[r+1][init_mask] = 1;
        for (int i=r; i>=1; i--) {
            int cur_mask = 0;
            for (int k=1; k<=c; k++)
                if (grid[i][k] == '+') cur_mask += (1 << (k - 1));

            int sz = ans[r].size();
            for (int j=0; j<sz; j++) {
                int tmp_mask = cur_mask;
                for (auto &pos : ans[i][j]) {
                    tmp_mask = tmp_mask ^ pos;
                    tmp_mask = tmp_Mask ^ (pos + 1);
                }

                dp[i][tmp_mask] += dp[i+1][tmp_mask] % MOD;
                dp[i][tmp_mask] %= MOD;
            }
        }


    }

    return 0;
}