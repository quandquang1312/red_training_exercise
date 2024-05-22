// https://cses.fi/problemset/task/1690/

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;
int n;
vector<int> adj[22];
int dp[21][(1 << 20) + 2];

int solve(int idx, int mask) {
    if (mask == 0 && idx == n) return 1;
    if (idx == n || mask == 0) return 0;

    if (dp[idx][mask] != -1) return dp[idx][mask] % MOD;

    int ans = 0;
    for (auto &city : adj[idx]) {
        if (!(mask & (1 << (city - 1)))) continue;
        int new_mask = mask ^ (1 << (city - 1));
        int tmp = solve(city, new_mask) % MOD;
        ans += tmp;
        ans %= MOD;
    }

    return dp[idx][mask] = ans % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int m;
    cin >> n >> m;
    memset(dp, -1, sizeof dp);

    for (int i=0; i<m; i++) {
        int src, dst;
        cin >> src >> dst;
        adj[src].push_back(dst);
    }

    int mask = (1 << n) - 1;
    mask = mask ^ (1 << 0);

    int ans = solve(1, mask);

    cout << ans << endl;

    return 0;
}