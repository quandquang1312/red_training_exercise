// https://codejam.lge.com/problem/25123

#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<pair<int, int>> dp1, dp2;
pair<int, int> dfs_1(int u, int par, vector<vector<int>>& adj, string tr) {
    if (dp1[u].first != -1) return dp1[u];
    int ans = 0, cnt = 1;
    for (auto &v : adj[u]) {
        if (v == par || tr[v-1] == tr[u-1]) continue;
        pair<int, int> tmp_ans = dfs_1(v, u, adj, tr);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    return dp1[u] = {1 + ans, cnt};
}

pair<int, int> dfs_2(int u, int par, vector<vector<int>>& adj, string tr) {
    if (dp2[u].first != -1) return dp2[u];
    int ans = 0, cnt = 1;
    for (auto &v : adj[u]) {
        if (v == par || tr[v-1] == tr[u-1] || v < u) continue;
        pair<int, int> tmp_ans = dfs_2(v, u, adj, tr);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    return dp2[u] = {1 + ans, cnt};
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
        pair<int, int> tmp_ans = dfs_1(i, 0, adj, tr);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    for (int i=1; i<=n; i++) {
        pair<int, int> tmp_ans = dfs_2(i, 0, adj, tr);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    cout << ans << " " << (ans != 1 ? cnt/2 : cnt) << '\n';
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
        dp1.assign(n+1, {-1, -1});
        dp2.assign(n+1, {-1, -1});
        vector<int> par(n + 1);
        for (int i=1; i<=n; i++) cin >> par[i];
        if (n <= 1000) sub_1(n, tr, par);
        else sub_1(n, tr, par);
    }

    return 0;
}