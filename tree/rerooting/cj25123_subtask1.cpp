// https://codejam.lge.com/problem/25123

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<pair<int, int>> dp;
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

void rerooting(int u, int par, vector<vector<int>>& adj) {
    if (dp[u].first > ans_sub2.first) ans_sub2 = dp[u];
    else if (dp[u].first == ans_sub2.first) ans_sub2.second += dp[u].second;
    
    vector<int>& nodes = adj[u];

    int n = nodes.size();
    vector<pair<int, int>> prefix(n + 5, {0, 0});
    vector<pair<int, int>> suffix(n + 5, {0, 0});

    for (int i=0; i<n; i++) {
        int v = nodes[i];
        if (dp[v].first == prefix[i].first) {
            prefix[i + 1] = { dp[v].first, dp[v].second + prefix[i].second };
        } else if (dp[v].first > prefix[i].first) {
            prefix[i + 1] = dp[v];
        } else {
            prefix[i + 1] = prefix[i];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int v = nodes[i];
        if (dp[v].first == suffix[i + 1].first) {
            suffix[i] = { dp[v].first, dp[v].second + suffix[i + 1].second };
        } else if (dp[v].first > suffix[i + 1].first) {
            suffix[i] = dp[v];
        } else {
            suffix[i] = suffix[i + 1];
        }
    }

    for (int i=0; i<n; i++) {
        int v = nodes[i];
        if (v == par) continue;

        // detach v from u
        pair<int, int> original_u = dp[u], original_v = dp[v];

        if (dp[u].first == dp[v].first + 1) {
            if (dp[u].second == dp[v].second) {
                dp[u] = {0, 1};

                pair<int, int> tmp_dpu;
                if (i == 0) tmp_dpu = suffix[i + 1];
                else if (i == n - 1) tmp_dpu = prefix[i];
                else {
                    pair<int, int> leftMax = prefix[i];
                    pair<int, int> rightMax = suffix[i + 1];

                    if (leftMax.first > rightMax.first) tmp_dpu = leftMax;
                    else if (rightMax.first > leftMax.first) tmp_dpu = rightMax;
                    else tmp_dpu = {leftMax.first, leftMax.second + rightMax.second };
                }

                if (dp[u].first == tmp_dpu.first) {
                    dp[u].first += tmp_dpu.second;
                } else if (tmp_dpu.first > dp[u].first) {
                    dp[u] = tmp_dpu;
                }
                dp[u].first += 1;
            } else {
                dp[u].second -= dp[v].second;
            }
        }

        // attach u to v
        if (dp[u].first + 1 == dp[v].first) dp[v].second += dp[u].second;
        else if (dp[u].first + 1 > dp[v].first) dp[v] = { dp[u].first + 1, dp[u].second };

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

void sub_2(int n, string& tr, vector<int> par) {
    vector<vector<int>> adj(n+1);
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

    pair<int, int> ttl {0, 0};
    for (auto &e : nodes) {
        ans_sub2 = {0, 0};
        ans_sub2 = dfs(e, 0, adj);
        ans_sub2 = {0, 0};
        rerooting(e, 0, adj);
        if (ans_sub2.first == ttl.first) {
            if (ans_sub2.first != 1) ttl.second += (ans_sub2.second / 2);
            else ttl.second += ans_sub2.second;
        }
        else if (ans_sub2.first > ttl.first) {
            ttl = { ans_sub2.first, ans_sub2.second};
            if (ttl.first != 1) ttl.second /= 2;
        }
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