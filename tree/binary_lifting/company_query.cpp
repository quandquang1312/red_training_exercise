// https://cses.fi/problemset/task/1687

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> up, adj;
const int LOG = 20;

// Binary Lifting
void dfs(int u, int p) {
    up[u][0] = p;

    for (auto &v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}

void fillUp(int n) {
    for (int l=1; l<LOG; l++) 
        for (int i=1; i<=n; i++) 
            if (up[i][l-1] != -1) up[i][l] = up[up[i][l-1]][l-1];
}

int query(int u, int k) {
    for (int i=0; i<LOG; i++) {
        if (k & (1 << i)) {
            u = up[u][i];
            if (u == -1) break;
        }
    }

    return u;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;

    adj.resize(n + 1);
    up.resize(n + 1, vector<int>(LOG, -1));

    for (int i=2, x; i<=n; i++) {
        cin >> x;
        adj[i].push_back(x);
        adj[x].push_back(i);
    };

    dfs(1, -1);
    fillUp(n);

    while (q--) {
        int u, k;
        cin >> u >> k;

        int ans = query(u, k);
        cout << ans << '\n';
    }

    return 0;
}