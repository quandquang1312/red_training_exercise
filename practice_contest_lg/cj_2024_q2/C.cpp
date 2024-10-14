// https://codejam.lge.com/contest/problem/1322/3

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e13;

// vector<vector<int>> adj;
vector<int> L, R;

int N;
vector<vector<int>> capacity, g_capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && g_capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, g_capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(N);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            g_capacity[prev][cur] -= new_flow;
            g_capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
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

        L.assign(m + 1, 0);
        R.assign(m + 1, 0);
        adj.assign(n + m + 2, vector<int>(0));
        capacity.assign(n + m + 2, vector<int>(n + m + 2, 0));
        int possible = true;
        int lst = -1;

        // MaxFlow o_graph(n + m + 2);

        // Add edge from robot to building
        for (int u=1; u<=n; u++) {
            int g, v; cin >> g;
            while (g--) {
                cin >> v;
                // adj[v].push_back(u);
                v = n + v;
                adj[u].push_back(v);
                adj[v].push_back(u);
                capacity[u][v] = 1;
                // o_graph.addEdge(u, v, 1);
            } 
        }

        // LR
        for (int i=1; i<=m; i++) {
            cin >> L[i] >> R[i];
        }

        // Chexk -1 case
        for (int i=1; i<=m && possible; i++) 
            if (L[i] >= adj[i+n].size() + 1) possible = false;

        if (possible == false) {
            for (int i=0; i<m; i++)
                cout << "-1 ";
            cout << "\n";
            continue;
        }

        int sink = n + m + 1;
        N = sink + 1;
        // Add edge from building to sink
        for (int i=n+1; i<=n+m; i++) {
            adj[i].push_back(sink);
            adj[sink].push_back(i);
            // o_graph.addEdge(i, sink, R[i - n]);
            capacity[i][sink] = R[i - n];
        }

        for (int i=1; i<=n; i++) {
            adj[0].push_back(i);
            adj[i].push_back(0);
            // graph.addEdge(0, i, b); // b = 1 case
        }

        for (int b=1; b<=m; b++) {
            // MaxFlow graph = o_graph;
            // Add 0 (source) to n robots
            for (int i=1; i<=n; i++) {
                capacity[0][i] = b;
                // graph.addEdge(0, i, b); // b = 1 case
            }

            g_capacity = capacity;

            int ans_b = maxflow(0, sink);
            cout << ans_b << " ";
            if (lst == ans_b) {
                for (int j=b+1; j<=m; j++)
                    cout << ans_b << " ";
                cout << "\n";
                break;
            } else {
                lst = ans_b;
            }
        }
    }

    return 0;
}