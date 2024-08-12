// https://codejam.lge.com/problem/25123

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<pair<int, int>> dp, dp2;
pair<int, int> ans_sub2;

pair<int, int> dfs(int u, int par, vector<vector<int>>& adj, string tr) {
    int ans = 0, cnt = 1;
    for (auto &v : adj[u]) {
        if (v == par || tr[v-1] == tr[u-1]) continue;
        pair<int, int> tmp_ans = dfs(v, u, adj, tr);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    return dp[u] = {1 + ans, cnt};
}

void sub_1(int n, string tr, vector<int> par) {
    vector<vector<int>> adj(n+1);
    for (int i=1; i<=n; i++) {
        if (par[i] == 0) continue;
        adj[i].push_back(par[i]);
        adj[par[i]].push_back(i);
    }

    int cnt = 0, ans = 0;
    for (int i=1; i<=n; i++) {
        pair<int, int> tmp_ans = dfs(i, 0, adj, tr);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    cout << ans << " " << (ans != 1 ? cnt/2 : cnt) << '\n';
}

void rerooting(int u, int par, vector<vector<int>>& adj, string tr) {
    if (dp2[u].first > ans_sub2.first) ans_sub2 = dp2[u];
    else if (dp2[u].first == ans_sub2.first) ans_sub2.second += dp2[u].second;

    for (auto &v : adj[u]) {
        if (v == par || tr[v-1] == tr[u-1]) continue;

        // detach v from u
        pair<int, int> original_u = dp2[u], original_v = dp[v];

        dp2[u] = {0, 1};
        for (auto &w : adj[u]) {
            if (w == v) continue;
            if (dp[w].first == dp2[u].first) dp2[u].second += dp[w].second;
            else if (dp[w].first > dp2[u].first) dp2[u] = dp[w];
        }
        dp[u].first += 1;

        // attach u to v
        if (dp2[u].first == dp[v].first) dp[v].second += dp2[u].second;
        else if (dp2[u].first > dp[v].first) dp[v] = dp2[u];
        dp2[v] = dp[v];

        rerooting(v, u, adj, tr);

        // backtrack
        dp2[u] = original_u;
        dp[v] = original_v;
    }
}

void sub_2(int n, string tr, vector<int> par) {
    vector<vector<int>> adj(n+1);
    dp2.assign(n + 1, {0, 0});
    for (int i=1; i<=n; i++) {
        if (par[i] == 0) continue;
        adj[i].push_back(par[i]);
        adj[par[i]].push_back(i);
    }

    ans_sub2 = {0, 1};
    dfs(1, 0, adj, tr);
    dp2[1] = dp[1];
    rerooting(1, 0, adj, tr);
    cout << ans_sub2.first << " " << ans_sub2.second << '\n';
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
        int n; cin >> n;
        dp.assign(n + 1, {0, 0});
        string tr; cin >> tr;
        vector<int> par(n + 1);
        for (int i=1; i<=n; i++) cin >> par[i];
        if (n <= 1000) sub_2(n, tr, par);
        else sub_2(n, tr, par);
    }

    return 0;
}