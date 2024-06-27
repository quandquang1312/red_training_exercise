#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n+1);
    vector<int> indegree(n+1, 0);

    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        indegree[b]++;
    }

    queue<int> q;
    for (int i=1; i<=n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty())
    {
        int v = q.front(); q.pop();
        topo.push_back(v);

        for (auto &u : adj[v]) {
            indegree[u]--;
            if (indegree[u] == 0) q.push(u);
        }
    }

    for (auto &e : topo) {
        cout << e << " ";
    }
    cout << endl;

    return 0;
}