// https://codejam.lge.com/problem/28311

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e9

int r, c, n, hx, hy; 
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool valid(int x, int y) {
    return (x >= 0 && x < r && y >= 0 && y < c);
}

vector<int> shortestPath(pair<int, int> st, vector<vector<char>>& grid, vector<pair<int, int>>& des, int& th) {
    vector<vector<int>> dist(r, vector<int>(c, INF));

    queue<pair<int, int>> q;
    q.push(st);
    dist[st.first][st.second] = 0;

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();

        for (int i=0; i<4; i++) {
            int new_x = x + dir[i][0], new_y = y + dir[i][1];
            if (!valid(new_x, new_y)) continue;
            if (grid[new_x][new_y] == 'W') dist[new_x][new_y] = min(dist[new_x][new_y], dist[x][y] + 1);
            else if (dist[new_x][new_y] > dist[x][y] + 1) {
                dist[new_x][new_y] = dist[x][y] + 1;
                q.push({new_x, new_y});
            }
        }
    }

    vector<int> ans;
    for (auto &e : des) {
        ans.push_back({dist[e.first][e.second]});
    }

    th = dist[hx][hy];

    return ans;
}

vector<int> filter(pair<int, int> st, vector<vector<char>>& grid, vector<pair<int, int>>& des) {
    vector<vector<int>> dist(r, vector<int>(c, INF));

    queue<pair<int, int>> q;
    q.push(st);
    dist[st.first][st.second] = 0;

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();

        for (int i=0; i<4; i++) {
            int new_x = x + dir[i][0], new_y = y + dir[i][1];
            if (!valid(new_x, new_y)) continue;
            if (grid[new_x][new_y] == 'W') dist[new_x][new_y] = min(dist[new_x][new_y], dist[x][y] + 1);
            else if (dist[new_x][new_y] > dist[x][y] + 1 && grid[new_x][new_y] != 'W') {
                dist[new_x][new_y] = dist[x][y] + 1;
                q.push({new_x, new_y});
            }
        }
    }

    vector<pair<int, int>> ans;
    for (auto &e : des) {
        if (dist[e.first][e.second] != INF) ans.push_back(e);
    }

    des = ans;
    vector<int> d;
    for (auto &e : des) {
        d.push_back(dist[e.first][e.second]);
    }

    return d;
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
        cin >> r >> c >> n >> hx >> hy;
        hx--, hy--;

        vector<pair<int, int>> pawns(n);
        for (int i=0; i<n; i++) {
            cin >> pawns[i].first >> pawns[i].second;
            pawns[i].first--, pawns[i].second--;
        }

        vector<vector<char>> grid(r, vector<char>(c));
        vector<pair<int, int>> walls;
        for (int i=0; i<r; i++) {
            for (int j=0; j<c; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'W') walls.push_back({i, j});
            }
        }

        vector<int> w2h = filter({hx, hy}, grid, walls);

        int tmp; 
        vector<int> original = shortestPath({hx, hy}, grid, pawns, tmp);
        int orignal_sum = 0;
        for (auto &e : original) orignal_sum += e;

        int net_ttl = 0;
        vector<int> net(walls.size(), 0);
        for (int d=0; d<n; d++) {
            auto pawn = pawns[d];
            int h2w;
            vector<int> p2w = shortestPath(pawn, grid, walls, h2w);

            for (int i=0; i<walls.size(); i++) {
                net[i] += min(p2w[i] + w2h[i], original[d]);
            }
        }

        for (auto &d : net) {
            net_ttl += orignal_sum - d; 
        }

        cout << orignal_sum << " " << net_ttl << "\n";
    }

    return 0;
}