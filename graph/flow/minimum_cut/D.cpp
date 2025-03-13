// https://codejam.lge.com/problem/24434

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

vector<vector<int>> adj, capacity;

// Maximum Flow
int bfs(int source, int sink, vector<int>& parent) {
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
                if (v == sink) return new_flow;
                q.push({v, new_flow});
            }
        } 
    }

    return 0;
}

int max_flow(int source, int sink, int total) {
    int flow = 0;
    vector<int> parent(total + 1);
    int new_flow;

    while (new_flow = bfs(source, sink, parent)) {
        flow += new_flow;
        int cur = sink;
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

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        int source = 0, sink = n + 1;

        adj.assign(sink + 1, vector<int>());
        capacity.assign(sink + 1, vector<int>(sink + 1, 0));

        vector<int> arr(n + 1);
        for (int i=1; i<=n; i++) cin >> arr[i];

        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            capacity[u][v] += w;
        }

        // source to vi >= 0
        // vi < 0 to sink
        int Vi = 0;
        for (int i=1; i<=n; i++) {
            if (arr[i] > 0) capacity[source][i] += arr[i], Vi += arr[i];
            if (arr[i] < 0) capacity[i][sink] += -arr[i]; 
        }

        // make graph
        for (int u=source; u<=sink; u++) {
            for (int v=source; v<=sink; v++) {
                if (capacity[u][v] > 0) {
                    // cout << u << " - " << v << ": " << capacity[u][v] << "\n";
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }
            }
        }

        int min_cut = max_flow(source, sink, sink + 1);
        cout << Vi - min_cut << "\n";
    }

    return 0;
}