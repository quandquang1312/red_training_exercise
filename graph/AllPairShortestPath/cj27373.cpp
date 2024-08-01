// https://codejam.lge.com/problem/27373

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX - 5
struct qu {
    int u, v, w;
};

vector<vector<int>> floyd(vector<vector<int>> dp, int n) {
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            if (dp[i][k] >= INF || i == k) continue;
            for (int j=1; j<=n; j++) {
                if (i == j || j == k) continue;
                if (dp[i][k] < INF && dp[k][j] < INF) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
    }

    return dp;
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

        vector<vector<int>> initial(n+1, vector<int>(n+1, INF)), dp;
        vector<vector<multiset<int>>> st(n+1, vector<multiset<int>>(n+1));
        for (int i=0; i<m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            if (c < initial[u][v]) {
                initial[u][v] = c;
                initial[v][u] = c;
            }
        }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (j == i) continue;
                if (initial[i][j] != INF) st[i][j].insert(initial[i][j]);
            }
        }

        for (int i=1; i<=n; i++) initial[i][i] = 0;

        dp = floyd(initial, n);
        int ans = 0;

        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) if (dp[i][j] != INF) ans += dp[i][j];

        stack<int> ans_st;
        stack<vector<vector<int>>> ans_vct;
        ans_vct.push(dp);
        ans_st.push(ans);

        while (q--) {
            int tp; cin >> tp;
            if (tp == 2) {
                int u, v, c;
                cin >> u >> v >> c;

                dp = ans_vct.top();

                if (c < dp[u][v]) {

                    ans = 0;
                    for (int i=1; i<=n; i++) {
                        for (int j=1; j<=n; j++) {
                            if (i == j) continue;
                            if (dp[i][u] != INF && dp[v][j] != INF) {
                                if (dp[i][j] > dp[i][u] + dp[v][j] + c) {
                                    dp[i][j] = dp[i][u] + dp[v][j] + c;
                                }
                            }
                            if (dp[i][v] != INF && dp[u][j] != INF) {
                                if (dp[i][j] > dp[i][v] + dp[u][j] + c) {
                                    dp[i][j] = dp[i][v] + dp[u][j] + c;
                                }
                            }
                            if (dp[i][j] != INF) ans += dp[i][j];
                        }
                    }
                }

                ans_vct.push(dp);
                ans_st.push(ans);
            } else if (tp == 1) {
                cout << ans_st.top() / 2 << " ";
            } else { // tp == 3
                if (ans_st.size() <= 1) continue;
                ans_st.pop();
                ans_vct.pop();
            }
        }

        cout << endl;
    }

    return 0;
}