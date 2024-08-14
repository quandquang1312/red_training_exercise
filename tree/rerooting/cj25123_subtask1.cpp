// https://codejam.lge.com/problem/25123

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<pair<int, int>> dp, dp2;
pair<int, int> ans_sub2;
vector<bool> visited;

pair<int, int> dfs(int u, int par, vector<vector<int>>& adj) {
    int ans = 0, cnt = 1;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        pair<int, int> tmp_ans = dfs(v, u, adj);
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
        pair<int, int> tmp_ans = dfs(i, 0, adj);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    cout << ans << " " << (ans != 1 ? cnt/2 : cnt) << '\n';
}

void rerooting(int u, int par, vector<vector<int>>& adj) {
    if (dp[u].first > ans_sub2.first) ans_sub2 = dp[u];
    else if (dp[u].first == ans_sub2.first) ans_sub2.second += dp[u].second;

    for (auto &v : adj[u]) {
        if (v == par) continue;

        // detach v from u
        pair<int, int> original_u = dp[u], original_v = dp[v];

        // cout << u << "-" << v << "\n";
        // cout << dp[u].first << "<->" << dp[v].first << '\n';
        dp[u] = {0, 1};
        for (auto &w : adj[u]) {
            if (w == v) continue;
            if (dp[w].first == dp[u].first) dp[u].second += dp[w].second;
            else if (dp[w].first > dp[u].first) dp[u] = dp[w];
        }
        dp[u].first += 1;

        // attach u to v
        if (dp[u].first + 1 == dp[v].first) dp[v].second += dp[u].second;
        else if (dp[u].first + 1 > dp[v].first) dp[v] = { dp[u].first + 1, dp[u].second };

        // cout << "dv: " << dp[v].first << " " << dp[v].second << '\n';

        rerooting(v, u, adj);

        // backtrack
        dp[u] = original_u;
        dp[v] = original_v;
    }
}

void mfill(int u, int par, vector<vector<int>>& adj) {
    if (visited[u]) return;
    visited[u] = true;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        mfill(v, u, adj);
    }
}

void sub_2(int n, string tr, vector<int> par) {
    vector<vector<int>> adj(n+1);
    dp2.assign(n + 1, {0, 0});
    visited.assign(n + 1, false);
    for (int i=1; i<=n; i++) {
        if (par[i] == 0) continue;
        if (tr[i-1] == tr[par[i]-1]) continue; 
        adj[i].push_back(par[i]);
        adj[par[i]].push_back(i);
    }

    vector<int> nodes;
    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            mfill(i, i, adj);
            nodes.push_back(i);
        }
    }

    // cout << "size: " << nodes.size() << '\n';

    pair<int, int> ttl {0, 0};
    for (auto &e : nodes) {
        ans_sub2 = {0, 1};
        ans_sub2 = dfs(e, 0, adj);
        // cout << ans_sub2.first << " " << ans_sub2.second << '\n';
        ans_sub2 = {0, 1};
        dp2[e] = dp[e];
        rerooting(e, 0, adj);
        if (ans_sub2.first == ttl.first) {
            if (ans_sub2.first != 1) ttl.second += (ans_sub2.second / 2);
            else ttl.second += ans_sub2.second;
        }
        else if (ans_sub2.first > ttl.first) {
            ttl = { ans_sub2.first, ans_sub2.second};
            if (ttl.first != 1) ttl.second /= 2;
        }
        // cout << ans_sub2.first << " " << (ans_sub2.first == 1 ? ans_sub2.second : ans_sub2.second / 2) << '\n';
    }

    cout << ttl.first << " " << ttl.second << '\n';
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
        sub_2(n, tr, par);
    }

    return 0;
}