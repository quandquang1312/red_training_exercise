// https://vjudge.net/problem/UVA-10116

#include <bits/stdc++.h>
using namespace std;

int r, c, st, cnt = 0;
vector<vector<char>> grid;
vector<vector<bool>> visited;
vector<vector<int>> trace;
pair<int, int> cycle_start, cycle_end;

bool checkValid(int x, int y) {
    return (x >= 1 && x <= r && y >= 1 && y <= c);
}

bool dfs(pair<int, int> cell) {
    int x = cell.first, y = cell.second;

    visited[x][y] = true;

    int new_x = x, new_y = y;
    if (grid[x][y] == 'S') new_x++;
    else if (grid[x][y] == 'N') new_x--;
    else if (grid[x][y] == 'W') new_y--;
    else if (grid[x][y] == 'E') new_y++;

    trace[x][y] = min(trace[x][y], cnt++);
    if (!checkValid(new_x, new_y)) {
        return false;
    }

    if (visited[new_x][new_y] == false) {
        if (dfs({new_x, new_y})) {
            return true;
        }
    } else {
        cycle_start = {new_x, new_y};
        cycle_end   = {x, y};
        return true;
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    r = 1, c = 1, st = 1;
    while ((cin >> r >> c >> st))
    {
        if (r + c + st == 0) break;
        grid.resize(r+5, vector<char>(c+5));
        trace.assign(r+5, vector<int>(c+5, 1e9));
        visited.assign(r+1, vector<bool>(c+5, false));
        cycle_start = {-1, -1};
        cnt = 0;

        for (int i=1; i<=r; i++) {
            for (int j=1; j<=c; j++) {
                cin >> grid[i][j];
            }
        }

        bool ret = dfs({1, st});

        if (cycle_start.first != -1 && cycle_start.second != -1 && ret == true)
        {
            int steps = trace[cycle_start.first][cycle_start.second];
            int loops = cnt - steps;
            printf("%d step(s) before a loop of %d step(s)\n", steps, loops);
        } else {
            printf("%d step(s) to exit\n", cnt);
        }
    }

    return 0;
}