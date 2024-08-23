// https://vjudge.net/problem/UVA-10448

#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<vector<int>> dp_1, dp_2;
int min_mask;

int solve(int u, int sm_up, int mask, const int dst, const int costRequired) {
    if (u == dst) {
        if (sm_up != costRequired) return 1e9;
        int cnt = __builtin_popcount(mask);
        int cnt_min_mask = __builtin_popcount(min_mask);
        if (cnt < cnt_min_mask) {
            min_mask = mask;
        }
        return cnt;
    }

    if (sm_up >= costRequired) return 1e9;

    if (dp_1[u][sm_up] != -1) return dp_1[u][sm_up];

    int ans = 1e9;
    for (auto &[v, w] : adj[u]) {
        int new_mask = mask | (1 << v);
        ans = min(ans, solve(v, sm_up + w, new_mask, dst, costRequired));
    }

    return dp_1[u][sm_up] = ans;
}

int solve2(int u, int sm_up, int roadTaken, int mask, const int dst, const int costRequired, const int nonode) {
    if (u == dst) {
        if (sm_up != costRequired) return 1e9;
        int cnt = __builtin_popcount(mask);
        if (cnt != nonode) return 1e9;
        return roadTaken;
    }

    if (sm_up >= costRequired) return 1e9;

    if (dp_2[u][sm_up] != -1) return dp_2[u][sm_up];

    int ans = 1e9;
    for (auto &[v, w] : adj[u]) {
        if (!(min_mask & (1 << v))) continue;
        int new_mask = mask | (1 << v);
        ans = min(ans, solve2(v, sm_up + w, 1 + roadTaken, new_mask, dst, costRequired, nonode));
    }

    return dp_2[u][sm_up] = ans;
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
        int n, m;
        cin >> n >> m;

        adj.clear();
        adj.resize(n+1);

        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        int q; cin >> q;
        while (q--) {
            int u, v, w;
            cin >> u >> v >> w;

            dp_1.assign(n + 1, vector<int>(w + 10, -1));
            dp_2.assign(n + 1, vector<int>(w + 10, -1));

            int initial_mask = (1 << u);
            min_mask = (1 << 22) - 1;
            int nonode = solve(u, 0, initial_mask, v, w);
            if (nonode != 1e9) {
                int rs = solve2(u, 0, 0, (1 << u), v, w, nonode);
                cout << "Yes " << rs << '\n';
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}