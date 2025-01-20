// https://codeforces.com/contest/2005/problem/E1

#include <bits/stdc++.h>
using namespace std;

#define MAXV 8
#define MAXN 305
int l, n, m;
vector<int> arr;
vector<vector<pair<int, int>>> coor(MAXV);
int dp[MAXN][MAXN][MAXN];

int solve(int idx, int x, int y) {
    if (x >= n || y >= m) return dp[idx][x][y] = 0;
    if (idx >= l) return dp[idx][x][y] = 0;

    if (dp[idx][x][y] != -1) return dp[idx][x][y];

    int tar = arr[idx];

    if (coor[tar].size() == 0) return dp[idx][x][y] = 0;

    int ans = 0;
    for (auto &[px, py] : coor[tar]) {
        if (px < x || py < y) continue;
        int tmp = solve(idx + 1, px + 1, py + 1);
        if (tmp == 0) ans = 1;
    }

    return dp[idx][x][y] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        cin >> l >> n >> m;

        // preprocess
        arr.resize(l);
        for (int i=0; i<MAXV; i++) coor[i].clear();
        memset(dp, -1, sizeof dp);

        for (int i=0; i<l; i++) cin >> arr[i];

        for (int i=0, x; i<n; i++) {
            for (int j=0; j<m; j++) {
                cin >> x;
                coor[x].push_back({i, j});
            }
        }

        int ans = solve(0, 0, 0);
        cout << (ans == 1? "T" : "N") << "\n";
    }

    return 0;
}