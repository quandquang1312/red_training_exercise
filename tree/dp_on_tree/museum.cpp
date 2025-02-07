// https://oj.uz/problem/view/CEOI17_museum

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 1e4 + 5;

int dp[MAXN][MAXN][2];
int sz[MAXN];
vector<pair<int, int>> adj[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k, x; cin >> n >> k >> x;

    // dp[i][j][0]: minimum cost to take j nodes starting from node i,
    // dp[i][j][1]: minimum cost to take j nodes starting from node i, going back to its parent

    for (int i=1; i<=n; i++) {
        for (int j=2; j<=n; j++) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }

    for (int i=1, u, v, w; i<n; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    function<int(int,int)> findSize = [&] (int u, int p) -> int {
        sz[u] = 1;
        for (auto &[v, _] : adj[u]) {
            if (v == p) continue;
            sz[u] += findSize(v, u);
        }
        return sz[u];
    };

    findSize(x, 0);

    function<void(int, int)> dfs = [&] (int u, int p) -> void {
        int total = 1;
        for (auto &[v, w] : adj[u]) {
            if (v == p) continue;
            dfs(v, u);

            for (int i=total; i>=0; i--) {
                for (int j=0; j<=sz[v]; j++) {
                    // going others first, going back -> go to v, not going back
                    dp[u][i + j][0] = min(dp[u][i + j][0], dp[u][i][1] + dp[v][j][0] + w);

                    // going to v first, going back -> going to others, not going back
                    dp[u][i + j][0] = min(dp[u][i + j][0], dp[u][i][0] + dp[v][j][1] + 2 * w);

                    // going to v and others, and go back
                    dp[u][i + j][1] = min(dp[u][i + j][1], dp[u][i][1] + dp[v][j][1] + 2 * w);
                }
            }

            total += sz[v];
        }
    };

    dfs(x, 0);

    cout << dp[x][k][0] << "\n";

    return 0;
}