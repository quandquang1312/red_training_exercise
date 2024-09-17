// https://codeforces.com/contest/25/problem/C
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

    int n; cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));

    int ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> dist[i][j];
            if (i != j) ans += dist[i][j];
        }
    }

    int m; cin >> m;
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        u--, v--;

        if (w < dist[u][v]) {
            ans = 0;
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    if (i == j) continue;
                    if (dist[i][j] > dist[i][u] + dist[v][j] + w)
                        dist[i][j] = dist[i][u] + dist[v][j] + w;
                    if (dist[i][j] > dist[i][v] + dist[u][j] + w)
                        dist[i][j] = dist[i][v] + dist[u][j] + w;

                    ans += dist[i][j];
                }
            }
        }

        cout << ans/2 << " ";
    }

    cout << endl;

    return 0;
}