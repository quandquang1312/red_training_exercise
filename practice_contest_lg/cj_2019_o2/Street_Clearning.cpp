// https://codejam.lge.com/problem/17434

#include <bits/stdc++.h>
using namespace std;

#define int long long

// eulerian path for undirected graph
void eulerian_path(int u, vector<vector<pair<int, int>>>& adj, vector<bool>& visited, vector<int>& path) {
    while (!adj[u].empty()) {
        auto [idx, v] = adj[u].back();
        adj[u].pop_back();

        if (visited[abs(idx)]) continue;
        visited[abs(idx)] = true;

        eulerian_path(v, adj, visited, path);
        path.push_back(-idx);
    }
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
        int n, m; cin >> n >> m;
        vector<vector<pair<int, int>>> adj(n + 1);

        vector<pair<int, int>> edges(m);
        vector<int> indegree(n + 1, 0);
        for (int i=0; i<m; i++) cin >> edges[i].first;
        for (int i=0; i<m; i++) cin >> edges[i].second;

        for (int i=1; i<=m; i++) {
            auto e = edges[i - 1];
            adj[e.first].push_back({i, e.second});
            adj[e.second].push_back({-i, e.first});
        }

        // Check if any node has more than 4 degree
        vector<int> odd_degree;
        for (int i=1; i<=n; i++) {
            if (adj[i].size() % 2) odd_degree.push_back(i);
        }

        if (odd_degree.size() > 4 || m == 1) {
            cout << "0\n0\n";
            continue;
        }

        // if have 4 odd degree node, so there will be 2 eulerian path
        // connect two to to merge it into 1 eulerian path
        if (odd_degree.size() == 4) {
            int u = odd_degree[2], v = odd_degree[3];
            adj[u].push_back({m + 1, v});
            adj[v].push_back({-(m + 1), u});
        }

        int st = (odd_degree.size() == 0 ? 1 : odd_degree[0]);

        vector<bool> visited(m + 2, false);
        vector<int> path;
        eulerian_path(st, adj, visited, path);

        // find the merge point ealier
        int breaking_edge = -1;
        for (int i=0; i<path.size(); i++) {
            if (abs(path[i]) == m + 1) {
                breaking_edge = i;
                break;
            }
        }

        // Case not a 2 eulerian path
        if (breaking_edge == -1) {
            int lst = path.back();
            path.pop_back();

            path.push_back(m + 1);
            path.push_back(lst);

            breaking_edge = path.size() - 2;
        }

        cout << breaking_edge << " ";
        for (int i=0; i<breaking_edge; i++) {
            cout << path[i] << " ";
        }

        cout << "\n" << path.size() - breaking_edge - 1 << " ";
        for (int i=breaking_edge + 1; i<path.size(); i++) {
            cout << path[i] << " ";
        }

        cout << "\n";
    }

    return 0;
}