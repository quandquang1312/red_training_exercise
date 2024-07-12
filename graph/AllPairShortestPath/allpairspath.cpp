// https://open.kattis.com/problems/allpairspath?tab=metadata

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

    int n, m, q;
    while (cin >> n >> m >> q)
    {
        if (n + m + q == 0) break;

        vector<vector<int>> mtr(n, vector<int>(n, 1e9)), dist;
        for (int i=0; i<n; i++) mtr[i][i] = 0;

        for (int i=0; i<m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            mtr[u][v] = min(mtr[u][v], w);
        }

        dist = mtr;

        for (int k=0; k<n; k++) {
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    if (dist[i][k] < 1e9 && dist[k][j] < 1e9)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                for (int t=0; t<n; t++) {
                    if ((dist[i][t] < 1e9 && dist[t][j] < 1e9)  && dist[t][t] < 0)
                        dist[i][j] = -1e9;
                }
            }
        }

        while (q--) {
            int u, v;
            cin >> u >> v;
            if (dist[u][v] == 1e9) cout << "Impossible\n";
            else if (dist[u][v] == -1e9) cout << "-Infinity\n";
            else cout << (dist[u][v]) << endl;
        }

        cout << endl;
    }

    return 0;
}