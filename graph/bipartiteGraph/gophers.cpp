// https://open.kattis.com/problems/gopher2?tab=metadata

#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;
vector<int> LeftMatch, RightMatch;
vector<vector<int>> adj;

bool kuhn(int u) {
    if (visited[u]) return false;
    visited[u] = true;

    for (int v : adj[u]) {
        if (LeftMatch[v] == -1 || kuhn(LeftMatch[v])) {
            LeftMatch[v]  = u;
            RightMatch[u] = v;
            return true;
        }
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, s, v;
    while (cin >> n >> m >> s >> v) {
        adj.clear();
        adj.assign(n, vector<int>());
        vector<complex<double>> gops(n), holes(m); 

        for (int i=0; i<n; i++) { double x, y; cin >> x >> y; gops[i] = {x, y}; };
        for (int i=0; i<m; i++) { double x, y; cin >> x >> y; holes[i] = {x, y}; };

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (abs(gops[i] - holes[j]) <= (s * v)) adj[i].push_back(j);
            }
        }

        LeftMatch.resize(n+m, -1);
        RightMatch.resize(n+m, -1);

        for (int i=0; i<n; i++) {
            if (RightMatch[i] != -1) continue;
            visited.resize(n+m, false);
            kuhn(i);
        }

        int ans = 0;
        for (int i=0; i<n; i++) if (RightMatch[i] == -1) ans++;
        cout << ans << endl;
    }

    return 0;
}