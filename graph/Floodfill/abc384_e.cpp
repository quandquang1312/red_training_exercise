// https://atcoder.jp/contests/abc384/tasks/abc384_e

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

    int h, w, X;
    cin >> h >> w >> X;

    pair<int, int> st;
    cin >> st.first >> st.second;
    st.first -= 1; st.second -= 1;

    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    auto isIn = [&](int xx, int yy) {
        return (xx >= 0 && xx < h && yy >= 0 && yy < w);
    };

    vector<vector<int>> arr(h, vector<int>(w));
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            cin >> arr[i][j];
        }
    }

    priority_queue<tuple<int, int, int>> q, neightbors;

    q.push({-arr[st.first][st.second], st.first, st.second});
    int strength = arr[st.first][st.second];

    vector<vector<bool>> visited(h, vector<bool>(w, false));
    visited[st.first][st.second] = true;

    while (!q.empty()) {
        auto [val, x, y] = q.top();
        val = -val;
        q.pop();

        for (int i=0; i<4; i++) {
            int new_x = x + dir[i][0];
            int new_y = y + dir[i][1];

            if (!isIn(new_x, new_y)) continue;
            if (visited[new_x][new_y]) continue;
            neightbors.push({-arr[new_x][new_y], new_x, new_y});
            visited[new_x][new_y] = true;
        }

        while (!neightbors.empty()) {
            auto [val, xx, yy] = neightbors.top();
            val = -val;
            double tmp = (strength * 1.0) / (1.0 * X);
            if ((val * 1.0) < tmp) {
                q.push({-val, xx, yy});
                strength += arr[xx][yy];
                visited[xx][yy] = true;
                neightbors.pop();
            } else {
                break;
            }
        }
    }

    cout << strength << "\n";

    return 0;
}