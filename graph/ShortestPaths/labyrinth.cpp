// https://cses.fi/problemset/task/1193

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<char>> arr(n, vector<char>(m));
    pair<int, int> st, en;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 'A') st = {i, j};
            if (arr[i][j] == 'B') en = {i, j};
        }
    }

    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    vector<vector<pair<int, int>>> trace(n, vector<pair<int, int>>(m, {-1, -1}));
    dist[st.first][st.second] = 0;

    queue<pair<int, int>> q;
    q.push(st);
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    auto valid = [](int x, int y, int n, int m) -> bool {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i=0; i<4; i++) {
            int newx = x + dir[i][0], newy = y + dir[i][1];

            if (!valid(newx, newy, n, m)) continue;
            if (arr[newx][newy] == '#') continue;

            if (dist[x][y] + 1 < dist[newx][newy]) {
                dist[newx][newy] = dist[x][y] + 1;
                q.push({newx, newy});
                trace[newx][newy] = {x, y};
            }
        }
    }

    // for (int i=0; i<n; i++) {
    //     for (int j=0; j<m; j++) {
    //         cout << dist[i][j] << " ";
    //     } cout << endl;
    // }

    if (dist[en.first][en.second] == 1e9) {
        printf("NO\n");
    } else {
        printf("YES\n%d\n", dist[en.first][en.second]);

        string ans = "";
        pair<int, int> cur = en;
        while (trace[cur.first][cur.second].first != -1) {
            int absx = cur.first - trace[cur.first][cur.second].first;
            int absy = cur.second - trace[cur.first][cur.second].second;

            if (absx == 0 && absy == -1) {
                ans.push_back('L');
            } else if (absx == 0 && absy == 1) {
                ans.push_back('R');
            } else if (absx == 1 && absy == 0) {
                ans.push_back('D');
            } else if (absx == -1 && absy == 0) {
                ans.push_back('U');
            }

            cur = trace[cur.first][cur.second];
        }
        reverse(ans.begin(), ans.end());
        printf("%s\n", ans.c_str()); //  << ans << '\n';
    }

    return 0;
}