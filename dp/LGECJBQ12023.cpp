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

int solve(int idx, int mask)
{
    if (idx > r) {
        if (mask == ((1 << c) - 1)) return 1;
        return 0;
    }

    if (dp[idx][mask] != -1) return dp[idx][mask];

    int current_mask = mask;
    for (int i=1; i<=c; i++) {
        if (grid[idx][i] == '+') {
            current_mask = current_mask ^ (1 << (i - 1));
        }
    }

    int res = 0;

    for (auto &vect : ans[idx]) {
        int tmp_mask = current_mask; 
        for (auto &e : vect) {
            tmp_mask = tmp_mask ^ (1 << (e - 1));
            tmp_mask = tmp_mask ^ (1 << e);
        }
        int tmp_ans = solve(idx+1, tmp_mask);
        tmp_ans %= MOD;
        res += tmp_ans;
        res %= MOD;
    }

    // no place switch
    int tmp_ans = solve(idx+1, current_mask);
    tmp_ans %= MOD;
    res += tmp_ans;
    res %= MOD;

    return dp[idx][mask] = res;
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

        int init_mask = 0;
        for (int i=0; i<c; i++) {
            if (str[i] == '+') init_mask += (1 << i);
        }

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

        int res = solve(1, init_mask);
        cout << res << endl;
    }

    return 0;
}