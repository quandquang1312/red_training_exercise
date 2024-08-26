// https://usaco.org/index.php?page=viewproblem2&cpid=717&lang=vi

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX
#define MOD 3

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #else
        freopen("visitfj.in", "r", stdin);
        freopen("visitfj.out", "w", stdout);
    #endif

    int n, t;
    cin >> n >> t;

    int arr[n][n];
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) cin >> arr[i][j];

    vector<vector<vector<int>>> dist(n+1, vector<vector<int>>(n+1, vector<int>(MOD, INF)));
    dist[0][0][0] = 0;

    // distance, timer, x, y
    priority_queue<tuple<int, int, int, int>> pq;
    pq.push({0, 0, 0, 0});

    auto checkValid = [](int x, int y, int n) {
        return (x >= 0 && x < n && y >= 0 && y < n);
    };

    int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    while (!pq.empty()) {
        auto [d, timer, x, y] = pq.top();
        pq.pop();

        d = -d;

        if (d > dist[x][y][timer]) continue;

        for (int i=0; i<4; i++) {
            int new_x = x + dir[i][0];
            int new_y = y + dir[i][1];

            if (!checkValid(new_x, new_y, n)) continue;
            int new_timer = (timer + 1) % MOD;
            int addition = (new_timer == 0) ? arr[new_x][new_y] : 0;
            if (d + t + addition < dist[new_x][new_y][new_timer]) {
                dist[new_x][new_y][new_timer] = d + t + addition;
                pq.push({-dist[new_x][new_y][new_timer], new_timer, new_x, new_y});
            }
        }
    }

    int ans = INF;
    for (int i=0; i<MOD; i++) ans = min(ans, dist[n-1][n-1][i]);

    cout << ans << endl;

    return 0;
}