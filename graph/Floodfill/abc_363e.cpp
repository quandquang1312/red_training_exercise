// https://atcoder.jp/contests/abc363/tasks/abc363_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e13;

int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> arr(n, vector<int>(m));
    queue<pair<int, int>> q;

    int edge_min = INF;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> arr[i][j];
            if (i == 0 || i == n-1 || j == 0 || j == m-1) edge_min = min(edge_min, arr[i][j]);
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (arr[i][j] == edge_min) {
                q.push({i, j});
                visited[i][j] = true;
            }
        }
    }

    int ans = n * m;
    for (int i=1; i<edge_min; i++) {
        cout << ans << "\n";
    }

    auto valid = [](int x, int y, int n, int m) {
        return (x >= 0 && x < n && y >= 0 && y < m);
    };

    while (edge_min <= k) {
        queue<pair<int, int>> q2;
        int new_min = INF;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            ans--;

            for (int i=0; i<4; i++) {
                int new_x = x + dir[i][1], new_y = y + dir[i][0];
                if (!valid(new_x, new_y, n, m)) continue;
                if (visited[new_x][new_y]) continue;
                if (arr[new_x][new_y] <= edge_min) {
                    visited[new_x][new_y] = true;
                    q.push({new_x, new_y});
                } else {
                    if (arr[new_x][new_y] < new_min) {
                        new_min = arr[new_x][new_y];
                        while (!q2.empty()) q2.pop();
                        visited[new_x][new_y] = true;
                        q2.push({new_x, new_y});
                    } else if (arr[new_x][new_y] == new_min) {
                        q2.push({new_x, new_y});
                        visited[new_x][new_y] = true;
                    }
                }
            }
        }

        // for this
        for (int i=edge_min; i<min(k, new_min); i++) {
            cout << edge_min << ": " << ans << "\n";
        }

        // cout << edge_min << ": " << ans << "\n";

        q = q2;
        if (new_min <= k) edge_min = new_min;
        else break;
    }

    for (int i=edge_min; i<=k; i++) {
        cout << edge_min << ": " << ans << "\n";
    }

    return 0;
}