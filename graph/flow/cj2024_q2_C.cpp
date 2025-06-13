// https://codejam.lge.com/problem/31812

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

vector<vector<int>> adj, capacity;

// Maximum Flow
int bfs(int source, int sink, vector<int>& parent, const vector<vector<int>>& tmp_cap) {
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INF});

    while (!q.empty()) {
        auto [u, cur_flow] = q.front();
        q.pop();

        for (auto &v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] - tmp_cap[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(cur_flow, capacity[u][v] - tmp_cap[u][v]);
                if (v == sink) return new_flow;
                q.push({v, new_flow});
            }
        }
    }

    return 0;
}

int max_flow(int source, int sink, int total) {
    vector<vector<int>> tmp_cap(total + 1, vector<int>(total + 1, 0));
    vector<int> parent(total + 1);
    int total_flow = 0;

    int new_flow;
    while ((new_flow = bfs(source, sink, parent, tmp_cap))) {
        total_flow += new_flow;
        int cur = sink;
        while (cur != source) {
            int prev = parent[cur];

            tmp_cap[prev][cur] += new_flow;
            tmp_cap[cur][prev] -= new_flow;

            // capacity[prev][cur] -= new_flow;
            // capacity[cur][prev] += new_flow;

            cur = prev;
        }
    }

    return total_flow;
}

int32_t main() {
    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        vector<int> L(m, 0), U(m, 0);

        int total_nodes = n + m + 1;
        adj.assign(total_nodes + 1, vector<int>());
        capacity.assign(total_nodes + 1, vector<int>(total_nodes + 1, 0));

        // source, sink 
        int source = 0, sink = total_nodes;

        auto addEdge = [&] (int u, int v, int c=0) -> void {
            adj[u].push_back(v);
            adj[v].push_back(u);
            capacity[u][v] += c;
        };

        auto changeCap = [&] (bool low) {
            for (int i=n+1; i<=n+m; i++) {
                int x = (low ? L[i - (n + 1)] : U[i - (n + 1)]);
                capacity[i][sink] = x;
            }
        };

        auto changeB = [&] (int b) {
            for (int i=1; i<=n; i++) {
                capacity[source][i] = b;
            }
        };

        // source to robots
        for (int i=1; i<=n; i++) addEdge(source, i);

        // robots to buildings
        for (int i=1, k, x; i<=n; i++) {
            cin >> k;
            for (int j=0; j<k; j++) {
                cin >> x;
                addEdge(i, n + x, 1);
            }
        }

        int totalL = 0;
        for (int i=0; i<m; i++) {
            cin >> L[i] >> U[i];
            totalL += L[i];
        }

        // buildings to sink
        for (int i=n+1; i<sink; i++) {
            addEdge(i, sink);
        }

        int b = 1;
        changeB(b);
        bool setLow = true;
        changeCap(setLow);

        // DEBUG
        auto debug = [&] () {
            for (int i=0; i<=sink; i++) {
                for (auto &v : adj[i]) {
                    cout << i << "-" << v << ": " << capacity[i][v] << "\n";
                }
                cout << "\n";
            }
        };

        while (b <= m) {
            // debug();

            int cur_flow = max_flow(source, sink, total_nodes);

            if (cur_flow < totalL) {
                cout << "-1 ";
                b++; changeB(b);
            } else if (setLow && (cur_flow >= totalL)) {
                setLow = false;
                changeCap(setLow);
            } else {
                cout << cur_flow << " ";
                b++; changeB(b);
            }
        }

        cout << "\n";
    }

    return 0;
}
