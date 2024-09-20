// https://vjudge.net/problem/UVA-10259

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> dp;
vector<vector<int>> pennies;

bool isIn(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

int dfs(int x, int y) {
    if (!isIn(x, y)) return 0;

    if (dp[x][y] != -1) return dp[x][y];

    int ans = 0;
    for (int i=-k; i<=k; i++) {
        int new_x = x + i;
        int new_y = y + i;
        if (isIn(new_x, y) && (pennies[new_x][y] > pennies[x][y])) ans = max(ans, dfs(new_x, y));
        if (isIn(x, new_y) && (pennies[x][new_y] > pennies[x][y])) ans = max(ans, dfs(x, new_y));
    }

    return dp[x][y] = ans + pennies[x][y];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    for (int t=0; t<tc; t++) {
        if (t) puts("");
        cin >> n >> k;

        dp.assign(n, vector<int>(n, -1));
        pennies.assign(n, vector<int>(n));

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                cin >> pennies[i][j];
            }
        }

        int ans = dfs(0, 0);
        printf("%d\n", ans);
    }

    return 0;
}