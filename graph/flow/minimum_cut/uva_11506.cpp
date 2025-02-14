// https://vjudge.net/contest/174055#problem/F

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;

vector<vector<int>> adj, capacity;

// Maximum Flow
int bfs(int source, int stink, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INF});

    while (!q.empty()) {
        auto [u, flow] = q.front();
        q.pop();

        for (auto &v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == stink) return new_flow;
                q.push({v, new_flow});
            }
        } 
    }

    return 0;
}

int max_flow(int source, int stink, int total) {
    int flow = 0;
    vector<int> parent(total + 1);
    int new_flow;

    while (new_flow = bfs(source, stink, parent)) {
        flow += new_flow;
        int cur = stink;
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        int total_n = 2 + (n - 2) * 2;
        int source = 0, sink = total_n - 1;


        adj.assign(total_n + 1, vector<int>());
        capacity.assign(total_n + 1, vector<int>(total_n + 1, 0));

        for (int i=0, idx, c; i<n-2; i++) {
            cin >> idx >> c;
            idx--;

            int u = idx * 2 - 1;
            int v = idx * 2;

            capacity[u][v] = c;
            capacity[v][u] = c;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i=0, idx1, idx2, w; i<m; i++) {
            cin >> idx1 >> idx2 >> w;
            idx1--, idx2--;

            int u1, v1, u2, v2;

            if (idx2 == n - 1) idx2 = sink;

            u1 = idx1 * 2 - 1;
            v1 = idx1 * 2;

            u2 = idx2 * 2 - 1;
            v2 = idx2 * 2;

            if (idx1 == source) u1 = v1 = source;

            if (idx2 == sink) u2 = v2 = sink;

            capacity[u1][v2] = w;
            capacity[u2][v1] = w;

            adj[u1].push_back(v2);
            adj[v2].push_back(u1);

            adj[u2].push_back(v1);
            adj[v1].push_back(u2);
        }

        int ans = max_flow(source, sink, total_n);
        cout << ans << "\n";
    }

    return 0;
}