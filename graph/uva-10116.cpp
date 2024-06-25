// https://vjudge.net/problem/UVA-10116

#include <bits/stdc++.h>
using namespace std;

#define MAXN 12

int r, c, st, cnt = 0;
char color[MAXN][MAXN], grid[MAXN][MAXN];
vector<vector<pair<int, int>>> parent;
pair<int, int> cycle_start, cycle_end;

bool checkValid(int x, int y) {
    return (x >= 0 && x < r && y >= 0 && y < c);
}

bool dfs(pair<int, int> cell) {
    int x = cell.first, y = cell.second;

    color[x][y] = 1;

    int new_x = x, new_y = y;
    if (grid[x][y] == 'S') new_x--;
    else if (grid[x][y] == 'N') new_x++;
    else if (grid[x][y] == 'W') new_y--;
    else if (grid[x][y] == 'E') new_y++;

    cout << new_x << "-" << new_y << endl;

    if (!checkValid(new_x, new_y)) {
        return false;
    }

    cnt++;
    cout << "cnt: " << cnt << endl;

    if (color[new_x][new_y] == 0) {
        parent[new_x][new_y] = {x, y};
        if (dfs({new_x, new_y})) {
            return true;
        }
    } else if (color[new_x][new_y] == 1) {
        cycle_start = {new_x, new_y};
        cycle_end   = {x, y};
        return true;
    }

    color[x][y] = 2;
    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> r >> c >> st;

    parent.resize(r+1, vector<pair<int, int>>(c+1));
    cycle_start = {-1, -1};

    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            cin >> grid[i][j];
        }
    }

    dfs({0, st-1});

    if (cycle_start.first != -1 && cycle_start.second != -1)
    {
        cout << "I\n";
    } else {
        cout << "steps: " << cnt << endl;
    }


    return 0;
}