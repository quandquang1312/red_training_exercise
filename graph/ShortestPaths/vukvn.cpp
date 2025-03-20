// https://oj.vnoi.info/problem/vukvn

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<int>> dist(n, vector<int>(m, INF));
    queue<tuple<int, int>> init_q;
    pair<int, int> st, en;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '+') {
                init_q.push({i, j});
                dist[i][j] = 0;
            }
            if (grid[i][j] == 'V') st = {i, j};
            if (grid[i][j] == 'J') en = {i, j};
        }
    }

    vector<pair<int, int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    auto isIn = [&] (int i, int j) -> bool {
        return i >= 0 && i < n && j >= 0 && j < m;
    };

    while (!init_q.empty()) {
        auto [x, y] = init_q.front(); init_q.pop();

        for (auto &[xx, yy] : dir) {
            int new_x = x + xx, new_y = y + yy;
            if (!isIn(new_x, new_y)) continue;
            if (grid[new_x][new_y] != '+') {
                if (dist[x][y] + 1 < dist[new_x][new_y]) {
                    dist[new_x][new_y] = dist[x][y] + 1;
                    init_q.push({new_x, new_y});
                }
            }
        }
    }

    // for (int i=0; i<n; i++) {
    //     for (int j=0; j<m; j++) {
    //         cout << dist[i][j];
    //     }
    //     cout << "\n";
    // }

    auto check = [&] (int mid) -> bool {
        if (dist[st.first][st.second] < mid) return false;
        if (dist[en.first][en.second] < mid) return false;

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        queue<pair<int, int>> q;
        q.push(st);
        visited[st.first][st.second] = true;

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();

            for (auto &[xx, yy] : dir) {
                int new_x = x + xx, new_y = y + yy;
                if (!isIn(new_x, new_y)) continue;

                if (grid[new_x][new_y] == 'J') return true;
                if (dist[new_x][new_y] >= mid && !visited[new_x][new_y]) {
                    q.push({new_x, new_y});
                    visited[new_x][new_y] = true;
                } 
            }
        }

        return false;
    };

    int l = 0, r = INF;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << l << "\n";

    return 0;
}