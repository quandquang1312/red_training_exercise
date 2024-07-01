// https://vjudge.net/problem/UVA-12376

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++)
    {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n);
        vector<int> unit(n, 0);
        vector<int> memo(n, -1);
        vector<int> trace(n, -1);

        for (int i=0; i<n; i++) cin >> unit[i];

        int a, b;
        for (int i=0; i<m; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
        }

        int ans = 0, u = 0, en = -1;
        while (adj[u].size() != 0) {
            int tmp_max = 0;
            for (auto &v : adj[u]) {
                if (unit[v] > tmp_max) {
                    tmp_max = unit[v];
                    en = v;
                }
            }

            ans += tmp_max;
            u = en;
        }

        printf("Case %d: %d %d\n", t, ans, en);
    }

    return 0;
}