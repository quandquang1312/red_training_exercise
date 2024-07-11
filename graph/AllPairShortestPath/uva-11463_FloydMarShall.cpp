// https://vjudge.net/problem/UVA-11463

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

    int tc; cin >> tc;
    for (int t=0; t<tc; t++)
    {
        int n, m; cin >> n >> m;

        vector<vector<int>> AM(n, vector<int>(n,1e9));
        for (int i=0; i<n; i++) AM[i][i] = 0;

        for (int i=0; i<m; i++) {
            int u, v; cin >> u >> v;
            AM[u][v] = 1;
            AM[v][u] = 1;
        }

        for (int k=0; k<n; k++)
            for (int i=0; i<n; i++)
                for (int j=0; j<n; j++)
                    AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);

        int s, d;
        cin >> s >> d;

        int ans = -1;

        for (int i=0; i<n; i++) ans = max(ans, AM[s][i] + AM[i][d]);
        cout << "Case " << t+1 << ": " << ans << endl;
    }

    return 0;
}