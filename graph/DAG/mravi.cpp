// https://open.kattis.com/problems/mravi

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<pair<int, int>> parent(n + 1);
    vector<int> indegree(n + 1, 0), needs(n + 1, 0);
    bool sp[n + 1][n + 1] {};

    for (int i=0, u, v, p, s; i<n-1; i++) {
        cin >> u >> v >> p >> s;
        parent[v] = {u, p};
        indegree[u]++;
        sp[v][u] = sp[u][v] = s;
    }

    vector<int> leaves;
    for (int i=1; i<=n; i++) {
        cin >> needs[i];
        if (indegree[i] == 0) {
            leaves.push_back(i);
        }
    }

    vector<double> min_liquid(n + 1, 0.0);

    queue<int> release_node;
    for (auto &u : leaves) {
        int p = parent[u].first;
        double rs_u;
        if (sp[u][p] == 1) {
            rs_u = (needs[u] * (100.0 * 100.0)) / (parent[u].second * parent[u].second);
            rs_u = (double) sqrt (rs_u);
        } else { // no superpower
            rs_u = (needs[u] * 100.0) / (parent[u].second);
        }
        min_liquid[u] = rs_u;
        min_liquid[p] = max(min_liquid[p], min_liquid[u]);

        indegree[p]--;
        if (indegree[p] == 0) release_node.push(p);
    }

    while (!release_node.empty()) {
        int u = release_node.front();
        release_node.pop();
        if (u == 1) break;

        int p = parent[u].first;

        indegree[p]--;
        if (indegree[p] == 0) release_node.push(p);

        double rs_u;
        if (sp[u][p] == 1) {
            rs_u = (min_liquid[u] * (100.0 * 100.0)) / (parent[u].second * parent[u].second);
            rs_u = (double) sqrt (rs_u);
        } else { // no superpower
            rs_u = (min_liquid[u] * 100.0) / (parent[u].second);
        }

        min_liquid[u] = rs_u;
        min_liquid[p] = max(min_liquid[p], min_liquid[u]);
    }

    printf("%.3f\n", min_liquid[1]);

    return 0;
}