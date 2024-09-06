// https://cses.fi/problemset/task/1693

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

// eulerian path directed graph
vector<int> hierholzer(int u, int n) {
    vector<int> used(n + 1, 0), st, ans;
    st.push_back(u);

    while (!st.empty()) {
        int v = st.back();
        if (used[v] < adj[v].size()) {
            st.push_back(adj[v][used[v]]);
            used[v]++;
        } else {
            ans.push_back(v);
            st.pop_back();
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<int> indegree(n + 1, 0), outdegree(n + 1, 0);
    adj.resize(n + 1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
        outdegree[u]++;
    }

    bool fl = true;
    for (int i=2; i<n; i++) {
        if (outdegree[i] != indegree[i]) fl = false;
    }

    if ((outdegree[1] != indegree[1] + 1) || (outdegree[n] != indegree[n] - 1) || !fl) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> ans = hierholzer(1, n);

    if (ans.size() != m + 1 || ans.back() != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (auto &e : ans) {
        cout << e << " ";
    }

    return 0;
}