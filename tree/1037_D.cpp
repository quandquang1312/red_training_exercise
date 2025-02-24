// https://codeforces.com/problemset/problem/1037/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> parent(n + 1, -1);

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> seq(n);
    for (int i=0; i<n; i++) cin >> seq[i];
 
    function<void(int, int)> dfs = [&] (int u, int p) -> void {
        parent[u] = p;
        for (auto &v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
        }
    };
    dfs(1, 0);

    queue<int> q;
    q.push(1);

    bool valid = true;

    if (seq[0] != 1) valid = false;

    int prev = 1;
    while (!q.empty() && valid) {
        int u = q.front(); q.pop();

        int sz = (u == 1 ? adj[u].size() : adj[u].size() - 1);

        vector<int> cur;
        set<int> st;

        for (int i=0; i<sz; i++, prev++) {
            st.insert(seq[prev]);
            cur.push_back(seq[prev]);
        }

        if (st.size() != sz) valid = false;
        for (auto &v : adj[u]) {
            if (v == parent[u]) continue;
            if (st.find(v) == st.end()) valid = false;
        } 

        if (!valid) break;
        for (auto &v : cur) q.push(v);
    }

    cout << (valid ? "Yes\n" : "No\n");

    return 0;
}