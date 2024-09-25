// https://codejam.lge.com/problem/17145

#include <bits/stdc++.h>
using namespace std;

int r, c;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<vector<int>> trace;
vector<char> trace_char;

bool checkIn(int x, int y) {
    return (x >= 1 && x <= r && y >= 1 && y <= c);
}

bool dfs(int x, int y, int cell, vector<vector<bool>> visited) {
    if (!checkIn(x, y)) return false;
    if (visited[x][y]) return false;
    if (cell == r * c) return true;

    visited[x][y] = true;

    bool ans = false;
    for (int i=0; i<4; i++) {
        int new_x = x + dir[i][0], new_y = y + dir[i][1];
        if (!checkIn(new_x, new_y)) continue;
        if (visited[new_x][new_y]) continue;
        bool rs_tmp = dfs(new_x, new_y, cell + 1, visited);
        if (rs_tmp) {
            ans = true;
            trace[x][y] = i;
            break;
        }
        visited[new_x][new_y] = false;
    }

    return ans;
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
        int st_x, st_y;
        cin >> r >> c >> st_x >> st_y;

        vector<vector<bool>> visited(r + 1, vector<bool>(c + 1, false));
        trace.assign(r + 1, vector<int>(c + 1, -1));

        int ans = dfs(st_x, st_y, 1, visited);
        if (!ans) {
            cout << "IMPOSSIBLE\n";
        } else {
            // cout << "Implementing\n";
            int x = st_x, y = st_y;
            while (trace[x][y] != -1) {
                int d = trace[x][y];
                char m;
                if (d == 0) {
                    cout << "R";
                } else if (d == 1) {
                    cout << "D";
                } else if (d == 2) {
                    cout << "L";
                } else {
                    cout << "U";
                }

                x = x + dir[d][0];
                y = y + dir[d][1];
            }
            cout << endl;
        }
    }


    return 0;
}