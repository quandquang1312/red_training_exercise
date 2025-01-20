// https://codeforces.com/contest/2034/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<vector<char>> grid(n + 1, vector<char>(m + 1));
        vector<vector<bool>> visited(n + 2, vector<bool>(m + 2, false));
        vector<pair<int, int>> graph[n + 2][m + 2];

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'U') graph[i-1][j].push_back({i, j});
                if (grid[i][j] == 'D') graph[i+1][j].push_back({i, j});
                if (grid[i][j] == 'R') graph[i][j+1].push_back({i, j});
                if (grid[i][j] == 'L') graph[i][j-1].push_back({i, j});
            }
        }

        queue<pair<int, int>> q;
        for (int i=1; i<=m; i++) {
            q.push({0, i}), visited[0][i] = true;
            q.push({n + 1, i}), visited[n + 1][i] = true;
        }

        for (int i=1; i<=n; i++) {
            q.push({i, 0}), visited[i][0] = true;
            q.push({i, m + 1}), visited[i][m + 1] = true;
        }

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            for (auto &[x, y] : graph[i][j]) {
                if (!visited[x][y]) {
                    visited[x][y] = true;
                    q.push({x, y});
                }
            }
        }

        int ans = 0;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (visited[i][j] == 0 && \ 
                    ((visited[i-1][j] == 0) ||
                     (visited[i+1][j] == 0) ||
                     (visited[i][j-1] == 0) ||
                     (visited[i][j+1] == 0))
                ) {
                    ans++;
                }
            }
        }

        cout << ans << "\n";

    }

    return 0;
}