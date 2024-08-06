// https://codejam.lge.com/problem/25123

#include <bits/stdc++.h>
using namespace std;

#define int long long

pair<int, int> dfs(int u, int par, vector<vector<int>>& adj, string tr) {
    int ans = 0, cnt = 1;
    for (auto &v : adj[u]) {
        if (v == par || tr[v-1] == tr[u-1]) continue;
        pair<int, int> tmp_ans = dfs(v, u, adj, tr);
        if (tmp_ans.first == ans) cnt += tmp_ans.second;
        else if (tmp_ans.first > ans) ans = tmp_ans.first, cnt = tmp_ans.second;
    }

    return {1 + ans, cnt};
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
        vector<int> par(n + 1);
        for (int i=1; i<=n; i++) cin >> par[i];
        if (n <= 1000) sub_1(n, tr, par);
        else sub_1(n, tr, par);
    }

    return 0;
}