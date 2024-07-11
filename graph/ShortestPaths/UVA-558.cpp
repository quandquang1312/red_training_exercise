// https://vjudge.net/problem/UVA-558

#include <bits/stdc++.h>
using namespace std;

struct wormhole {
    int u, v, w;
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    for (int t=0; t<tc; t++) {
        int n, m;
        cin >> n >> m;

        vector<wormhole> AL;
        for (int i=0; i<m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            AL.push_back(wormhole {u,v,w});
        }

        vector<int> dist(n, 1e9);
        dist[0] = 0;

        int x;
        for (int i=0; i<n; i++) {
            x = -1;
            for (auto &worm : AL) {
                if (dist[worm.u] + worm.w < dist[worm.v]) {
                    dist[worm.v] = max((int)-1e9, (int) (dist[worm.u] + worm.w));
                    x = worm.v;
                }
            }
        }

        if (x != -1) {
            cout << "possible\n";
        } else {
            cout << "not possible\n";
        }
    }

    return 0;
}