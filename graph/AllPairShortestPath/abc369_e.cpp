// https://atcoder.jp/contests/abc369/tasks/abc369_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

struct Edge {
    int u, v, w;
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    for (int i=0; i<=n; i++) dist[i][i] = 0;
    vector<Edge> Edges(m);

    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
        Edges[i] = {u, v, w};
    }

    // Floyd-Warshall
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;

        vector<int> b(k);
        for (int i=0; i<k; i++) {
            cin >> b[i];
            b[i]--;
        }

        int ans = INF;
    
        do {
            // for all cases 2^k
            for (int i=0; i<(1<<k); i++) {
                int cur_ans = 0, lst = 1;
                for (int j=0; j<k; j++) {
                    if (i & (1 << j)) { // 1-bit, connect to u, lst will be v
                        cur_ans += dist[lst][Edges[b[j]].u];
                        cur_ans += Edges[b[j]].w;
                        lst = Edges[b[j]].v;
                    } else { // 0-bit, take v
                        cur_ans += dist[lst][Edges[b[j]].v];
                        cur_ans += Edges[b[j]].w;
                        lst = Edges[b[j]].u;
                    }
                }

                cur_ans += dist[lst][n];

                ans = min(cur_ans, ans);
            }
        } while (next_permutation(b.begin(), b.end()));

        cout << ans << "\n";
    }

    return 0;
}