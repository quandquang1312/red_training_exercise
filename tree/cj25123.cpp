// https://codejam.lge.com/problem/25123

#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<int> dp;

int dfs(int u, vector<vector<int>> adj, string tr, int r) {
    if (dp[u] != 0) return dp[u];

    int ans = 0;
    for (auto &v : adj[u]) {
        if (v == r || tr[v-1] == tr[u-1]) continue;
        ans = max(ans, dfs(v, adj, tr, u));
    }

    return dp[u] = ans + 1;
}

void sub_1(int n, string tr, vector<int> par) {
    dp.assign(n+1, 0);
    vector<vector<int>> adj(n+1);
    for (int i=0; i<n; i++) {
        if (par[i] == 0) continue;
        adj[i+1].push_back(par[i]);
        adj[par[i]].push_back(i+1);
    }

    for (int i=1; i<=n; i++) {
        cout << i << ": ";
        for (auto &v : adj[i]) {
            cout << v << " ";
        } cout << endl;
    }

    for (int i=1; i<=n; i++) if (dp[i] == 0) dfs(i, adj, tr, 0);
    cout << "====\n";
    for (int i=1; i<=n; i++) {
        cout << i << ": " << dp[i] << '\n';
    }
}

void sub_2(int n, string tr, vector<int> par) {

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        string tr; cin >> tr;
        vector<int> par(n);
        for (int i=0; i<n; i++) cin >> par[i];
        if (n <= 1000) sub_1(n, tr, par);
        else sub_2(n, tr, par);
    }

    return 0;
}