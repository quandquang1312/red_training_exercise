// https://atcoder.jp/contests/abc222/tasks/abc222_f

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<pair<int, int>>> adj;
vector<pair<int, int>> dp; 
vector<int> D, ans;

int dfs(int u, int par) {
    int d = 0;
    for (auto &[v, w] : adj[u]) {
        if (v == par) continue;
        int ans_v = dfs(v, u) + w;
        if (ans_v >= dp[u].first) {
            dp[u].second = dp[u].first;
            dp[u].first = ans_v;
        } else if (ans_v > dp[u].second) {
            dp[u].second = ans_v;
        }
    }

    return max(D[u], dp[u].first);
}

void rerooting(int u, int par) {
    ans[u] = dp[u].first;

    vector<pair<int, int>> pre(adj[u].size() + 1, {0, 0}), suf(adj[u].size() + 1, {0, 0});
    for (int i=0; i<adj[u].size(); i++) {
        auto [tmp_v, tmp_w] = adj[u][i];
        int ans_v = max(D[tmp_v], dp[tmp_v].first) + tmp_w;
        pre[i+1] = pre[i];
        if (ans_v >= pre[i+1].first) {
            pre[i+1].second = pre[i+1].first;
            pre[i+1].first = ans_v;
        } else if (ans_v > pre[i+1].second) {
            pre[i+1].second = ans_v;
        }
    }

    for (int i=adj[u].size()-1; i>=0; i--) {
        auto [tmp_v, tmp_w] = adj[u][i];
        int ans_v = max(D[tmp_v], dp[tmp_v].first) + tmp_w;
        suf[i] = suf[i+1];
        if (ans_v >= suf[i].first) {
            suf[i].second = suf[i].first;
            suf[i].first = ans_v;
        } else if (ans_v > suf[i].second) {
            suf[i].second = ans_v;
        }
    }

    for (int i=0; i<adj[u].size(); i++) {
        auto [v, w] = adj[u][i];
        if (v == par) continue;

        // save ori
        pair<int, int> o_u = dp[u], o_v = dp[v];

        // detach
        // brute force
        // dp[u] = {0, 0};
        // for (auto &[tmp_v, tmp_w] : adj[u]) {
        //     if (tmp_v == v) continue;
        //     int ans_v = max(D[tmp_v], dp[tmp_v].first) + tmp_w;
        //     if (ans_v >= dp[u].first) {
        //         dp[u].second = dp[u].first;
        //         dp[u].first = ans_v;
        //     } else if (ans_v > dp[u].second) {
        //         dp[u].second = ans_v;
        //     }
        // }


        // int max_cost = max(dp[u].first, D[u]);
        // max_cost += w;

        vector<int> tmp_dp = {pre[i].first, pre[i].second, suf[i+1].first, suf[i+1].second};
        sort(tmp_dp.begin(), tmp_dp.end(), greater<int>());
        dp[u] = {tmp_dp[0], tmp_dp[1]};

        int max_cost = max(dp[u].first, D[u]);
        max_cost += w;

        // attach
        if (max_cost >= dp[v].first) {
            dp[v].second = dp[v].first;
            dp[v].first = max_cost;
        } else if (max_cost > dp[u].second) {
            dp[v].second = max_cost;
        }

        rerooting(v, u);

        dp[u] = o_u, dp[v] = o_v;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    adj.resize(n + 1);
    D.resize(n + 1);
    ans.resize(n + 1);
    dp.assign(n + 1, {0, 0});

    for (int i=1, u, v, w; i<n; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for (int i=1; i<=n; i++) cin >> D[i];

    dfs(1, 0);
    rerooting(1, 0);

    for (int i=1; i<=n; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}