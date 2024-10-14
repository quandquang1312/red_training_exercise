// https://atcoder.jp/contests/abc375/tasks/abc375_f

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    for (int i=1; i<=n; i++) dist[i][i] = 0;

    vector<tuple<int, int, int>> edges;
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<vector<int>> queries(q);
    set<int> tp1count;
    for (int d=0; d<q; d++) {
        int tp; cin >> tp;
        if (tp == 1) {
            int idx; cin >> idx; idx--;
            tp1count.insert(idx);
            queries[d] = {tp, idx};
        } else {
            int u, v; cin >> u >> v;
            queries[d] = {tp, u, v};
        }
    }

    for (auto i=0; i<m; i++) {
        if (!tp1count.count(i)) { // only add not remove edge
            auto [u, v, w] = edges[i];
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
        }
    }

    // Floyd-Warshall
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    reverse(queries.begin(), queries.end());
    vector<int> ans_vct;
    for (int d=0; d<q; d++) {
        auto e = queries[d];
        if (e.size() == 2) { // add the edge back to calculate the previous queries
            int idx = e[1];
            auto [u, v, w] = edges[idx];
            for (int i=1; i<=n; i++) {
                for (int j=1; j<=n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][u] + dist[v][j] + w);
                    dist[i][j] = min(dist[i][j], dist[i][v] + dist[u][j] + w);
                }
            }
        } else {
            int u = e[1], v = e[2];
            int ans = (dist[u][v] >= INF ? -1 : dist[u][v]);
            ans_vct.push_back(ans);
        }
    }

    reverse(ans_vct.begin(), ans_vct.end());
    for (auto ans : ans_vct) cout << ans << "\n";

    return 0;
}