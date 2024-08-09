// https://codeforces.com/contest/161/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

int dp[50010][510], dp2[50010][510], n, k, ans;
vector<vector<int>> adj;

void dfs(int u, int par) {
    dp[u][0] = 1;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
        for (int i=1; i<=500; i++) dp[u][i] += dp[v][i-1];
    }

    dp2[u][k] = dp[u][k];
    // Inlcude the path from vi -> u -> vj that has length k
    int addition = 0;
    for (int i=1; i<=k/2; i++) {
        if (k % 2 == 0 && i == k/2) addition += dp[u][i] * dp[u][k-i];
        else dp2[u][k] += dp[u][i] * dp[u][k-i];
    }
    // Exclude the paths from vi_va -> u -> vi_vb that has length k
    for (auto &v : adj[u]) {
        if (v == par) continue;
        for (int i=1; i<=k/2; i++) {
            if (k % 2 == 0 && i == k/2) addition -= dp[v][i-1] * dp[v][k-i-1];
            else dp2[u][i] -= dp[v][i-1] * dp[v][k-i-1];
        }
    }

    ans += dp2[u][k] + addition/2;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> k;
    adj.resize(n+1);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    cout << ans << endl;

    return 0;
}