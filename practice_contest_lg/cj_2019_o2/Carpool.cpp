// https://codejam.lge.com/problem/17280

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200050

bool visited[MAXN];
int RightMatch[MAXN], LeftMatch[MAXN];

bool kuhn(int u, vector<vector<int>>& adj) {
    for (int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i];

        if (visited[v]) continue;
        visited[v] = true;

        if (RightMatch[v] == -1 || kuhn(RightMatch[v], adj) == true) {
            RightMatch[v] = u;
            LeftMatch[u]  = v;
            return true;
        }
    }

    return false;
}

int solve(int m, vector<vector<int>>& adj) {
    int matching = 0;
    while (true) {
        memset(visited, false, sizeof visited);
        bool foundMatch = false;

        for (int i=0; i<m; i++) {
            if (LeftMatch[i] != -1) continue;
            if (kuhn(i, adj)) foundMatch = true, matching++;
        }

        if (foundMatch == false) break;
    }

    return matching;
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
        int n, m; cin >> n >> m;

        memset(visited, false, sizeof visited);
        for (int i=0; i<MAXN; i++) {
            RightMatch[i] = LeftMatch[i] = -1;
        }

        vector<int> riders(n), riders_rev(n);
        for (int i=0; i<n; i++) {
            cin >> riders[i];
            riders_rev[i] = -riders[i];
        }

        vector<pair<int, int>> drivers(m);
        for (auto &e : drivers) cin >> e.first >> e.second;

        sort(riders.begin(), riders.end());
        sort(riders_rev.begin(), riders_rev.end());

        vector<vector<int>> adj(m + n);
        for (int u=0; u<drivers.size(); u++) {
            auto e = drivers[u];
            cout << e.first << " -> ";
            // greater
            int pos_l = lower_bound(riders.begin(), riders.end(), e.first) - riders.begin();
            int pos_r = lower_bound(riders_rev.begin(), riders_rev.end(), -e.second) - riders_rev.begin();
            pos_r = n - pos_r;

            for (int i=pos_l; i < n && i <= pos_r; i++) {
                cout << riders[i] << " ";
                adj[u].push_back(m + i);
                adj[m + i].push_back(u);
            }
            cout << endl;
        }

        for (int i=0; i<m; i++) {
            cout << drivers[i].first << ": ";
            for (auto &e : adj[i]) {
                cout << e << " ";
            } cout << endl;
        }

        int ans = solve(m, adj);
        cout << ans << endl;
    }

    return 0;
}