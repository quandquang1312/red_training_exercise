// https://codejam.lge.com/problem/27373

#include <bits/stdc++.h>
using namespace std;

// #define int long long

struct qu {
    int u, v, w;
};

vector<vector<int>> floyd(vector<vector<int>> dp, int n) {
    vector<vector<int>> rs = dp;
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (dp[i][k] < 1e9 && dp[k][j] < 1e9)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    return rs;
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
        int n, m, q;
        cin >> n >> m >> q;

        vector<vector<int>> initial, dp;
        for (int i=0; i<m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            if (c < initial[u][v]) {
                initial[u][v] = c;
                initial[v][u] = c;
            }
        }

        for (int i=1; i<=n; i++) {
            dp[i][i] = 0;
        }

        dp = floyd(initial, n);

        stack<qu> queri;
        vector<vector<multiset<int>>> st(n+1, vector<multiset<int>>(n+1));
        while (q--) {
            int tp; cin >> tp;
            if (tp == 2) {
                int u, v, c;
                cin >> u >> v >> c;
                st[u][v].insert(c);
                st[v][u].insert(c);
                qu tmp {u, v, c};
                queri.push(tmp);

                if (c < dp[u][v]) {
                    dp[u][v] = *st[u][v].begin();
                    dp[v][u] = *st[v][u].begin();
        (dp, n);
                }
            } else if (tp == 1) {
                int ans = 0; 
                for (int i=1; i<=n; i++) {
                    for (int j=i+1; j<=n; j++)
                        ans += (dp[i][j] != 1e9 ? dp[i][j] : 0);
                }
                cout << ans << " ";
            } else { // tp == 3
                if (queri.empty()) continue;
                auto [u, v, c] = queri.top();
                queri.pop();
                auto it = st[u][v].find(c);
                if (it != st[u][v].end()) st[u][v].erase(it);
                it = st[v][u].find(c);
                if (it != st[v][u].end()) st[v][u].erase(it);

                if (!st[u][v].empty()) {
                    dp[u][v] = *st[u][v].begin();
                    dp[v][u] = *st[v][u].begin();
                } else {
                    dp[u][v] = 1e9;
                    dp[v][u] = 1e9;
                }

                floyd(dp, n);
            }
        }

        cout << endl;
    }

    return 0;
}