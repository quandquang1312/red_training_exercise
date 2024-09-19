// https://open.kattis.com/problems/honey?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 15

int dp[MAXN * 2 + 5][MAXN * 2 + 5][MAXN];
bool visited[MAXN * 2 + 5][MAXN * 2 + 5][MAXN];
int n;

int walk(int x, int y, int step) {
    if (step >= n) {
        return (x == MAXN && y == MAXN);
    }

    if (visited[x][y][step]) return dp[x][y][step];
    visited[x][y][step] = true;

    int ans = 0;

    ans += walk(x + 1, y + 1, step + 1);
    ans += walk(x + 1, y, step + 1);
    ans += walk(x, y + 1, step + 1);
    ans += walk(x - 1, y - 1, step + 1);
    ans += walk(x - 1, y, step + 1);
    ans += walk(x, y - 1, step + 1);

    return dp[x][y][step] = ans;
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
        cin >> n;

        memset(dp, 0, sizeof dp);
        memset(visited, false, sizeof visited);

        int ans = walk(MAXN, MAXN, 0);
        cout << ans << '\n';
    }

    return 0;
}