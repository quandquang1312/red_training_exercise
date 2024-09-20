// https://vjudge.net/problem/UVA-10544

#include <bits/stdc++.h>
using namespace std;

const string convert = "_ABCDEFGHIKLMNOPQRSTUVWXYZ";

int n, m;
vector<vector<int>> adj;
vector<bool> visited;
vector<set<string>> dp;

set<string> dfs(int u) {
    visited[u] = true;
    if (adj[u].size() == 0) {
        set<string> st;
        string rs = "";
        rs.push_back(convert[u]);
        st.insert(rs);
        return dp[u] = st;
    }

    string str = "";
    str.push_back(convert[u]);

    for (auto &v : adj[u]) {
        if (!visited[v]) dfs(v);

        for (auto &s : dp[v]) {
            string new_str = str;
            new_str.append(s);
            dp[u].insert(new_str);
        }
    }

    return dp[u];
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
        cin >> n >> m;

        adj.assign(n + 1, {});
        dp.clear();
        dp.resize(n + 1);
        visited.assign(n + 1, false);

        string ed;
        for (int i=0; i<m; i++) {
            cin >> ed;
            int u = ed[0] - 65 + 1, v = ed[1] - 65 + 1;
            adj[u].push_back(v);
        }

        for (int i=1; i<=n; i++) {
            if (!visited[i]) dfs(i);
        }

        int q; cin >> q;
        while (q--) {
            string str; cin >> str;
            int idx = str[0] - 65 + 1;
            int ans = 0;
            for (auto &e : dp[idx]) {
                ans++;
                if (e.size() != str.size()) continue;
                if (str.compare(e) == 0) break;
            }

            cout << str << ": " << ans << "\n";
        }
    }

    return 0;
}