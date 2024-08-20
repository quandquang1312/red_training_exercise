// https://usaco.org/index.php?page=viewproblem2&cpid=838

#include <bits/stdc++.h>
using namespace std;

bool topo_check(int n, vector<vector<int>>& adj, vector<int>& ans_topo) {
    vector<int> indegree(n + 1, 0), topo;
    for (int i=1; i<=n; i++) {
        for (auto &v : adj[i]) {
            indegree[v]++;
        }
    }

    priority_queue<int> q;
    for (int i=1; i<=n; i++) {
        if (indegree[i] == 0) q.push(-i);
    }

    while (!q.empty()) {
        int u = -q.top();
        q.pop();

        topo.push_back(u);

        for (auto &v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(-v);
        }
    }

    if (topo.size() == n) {
        ans_topo = topo;
        return true;
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #else
        freopen("milkorder.in", "r", stdin);
        freopen("milkorder.out", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> original_adj(m);
    vector<int> topo_ans;
    original_adj[0].resize(n + 1);

    for (int i=0, mi, x, u, v, lst; i<m; i++) {
        cin >> mi;
        original_adj[i].resize(mi);

        for (int j=0; j<mi; j++) {
            cin >> original_adj[i][j];
        }
    }

    int l = 0, r = m - 1;
    vector<int> topo;
    while (l < r) {
        int x = (l + r + 1) >> 1;

        vector<vector<int>> adj(n + 1);
        for (int i=0; i<x; i++) {
            for (int j=0; j<original_adj[i].size() - 1; j++) {
                int u = original_adj[i][j], v = original_adj[i][j + 1];
                adj[u].push_back(v);
            }
        }

        bool tmp_ans = topo_check(n, adj, topo);
        if (tmp_ans == true) {
            l = x;
        } else {
            r = x - 1;
        }
    }

    vector<vector<int>> adj(n + 1);
    for (int i=0; i<l; i++) {
        for (int j=0; j<original_adj[i].size() - 1; j++) {
            int u = original_adj[i][j], v = original_adj[i][j + 1];
            adj[u].push_back(v);
        }
    }
    topo_check(n, adj, topo);

    for (int i=0; i<n; i++) {
        if (i) cout << " ";
        cout << topo[i]; 
    }
    return 0;
}