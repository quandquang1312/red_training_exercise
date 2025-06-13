// https://codejam.lge.com/problem/32101

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

vector<bool> isBlack_a, isBlack_b, visited_a, visited_b;
vector<vector<int>> adj_a, adj_b;
vector<int> D_a, D_b;

void reset(int& n, vector<bool>& isBlack, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& D) {
    adj.assign(n + 1, vector<int>());
    D.assign(n + 1, 0);
    isBlack.assign(n + 1, false);
    visited.assign(n + 1, false);
}

void dfs(int start, int u, int black_cnt, vector<bool>& isBlack, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& D) {
    if (isBlack[u]) black_cnt++;
    if (black_cnt > 1) return;

    if (black_cnt == 1) D[start]++;

    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) dfs(start, v, black_cnt, isBlack, visited, adj, D);
    }

    visited[u] = false;
};

int solve(int& n, int& m, vector<bool>& isBlack, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& D) {
    cin >> n >> m;
    reset(n, isBlack, visited, adj, D);

    for (int i=0, u; i<m; i++) {
        cin >> u; isBlack[u] = true;
    }

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int f = 0;
    for (int i=1; i<=n; i++) {
        visited.assign(n + 1, false);
        dfs(i, i, 0, isBlack, visited, adj, D);
        f += D[i];
    }

    return f;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int na, ma, nb, mb;

        int fa = solve(na, ma, isBlack_a, visited_a, adj_a, D_a);
        int fb = solve(nb, mb, isBlack_b, visited_b, adj_b, D_b);

        int ans = 0;
        for (int i=1; i<=na; i++) {
            ans += D_a[i] * fb * i;
        }

        for (int i=1; i<=nb; i++) {
            ans += D_b[i] * fa * i;
        }

        cout << ans << "\n";
    }

    return 0;
}