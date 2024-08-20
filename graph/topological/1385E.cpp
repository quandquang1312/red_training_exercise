// https://codeforces.com/contest/1385/problem/E

/*
If the initial (without undirected edges) contain cycle, the answer is NO
Otherwise it is YES
Construct the graph in topological sorting order
The node i with topo order lower than the node j will be connect to j
*/

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);

        vector<int> indegree(n + 1, 0), topo(n + 1, 0);
        vector<pair<int, int>> edges(m);
        for (int i=0, ti, u, v; i<m; i++) {
            cin >> ti >> edges[i].first >> edges[i].second;

            u = edges[i].first;
            v = edges[i].second;

            if (ti == 1) {
                adj[u].push_back(v);
                indegree[v]++;
            }
        }

        queue<int> q;

        for (int i=1; i<=n; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        int cnt = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            cnt++;
            topo[u] = cnt;

            for (auto &v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) q.push(v);
            }
        }

        bool fl = true;
        for (int i=1; i<=n && fl; i++)
            if (indegree[i] != 0) fl = false; 

        if (!fl) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for (int i=0; i<m; i++) {
                if (topo[edges[i].first] > topo[edges[i].second]) swap(edges[i].first, edges[i].second);
                cout << edges[i].first << " " << edges[i].second << '\n';
            }
        }


    }

    return 0;
}