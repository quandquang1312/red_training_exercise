// https://vjudge.net/problem/LightOJ-1155

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 210;
const int INF  = 1e18;

vector<vector<int>> adj, capacity;

// Maximum Flow
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<tuple<int, int, int>> q;
    q.push({s, INF, -1});

    while (!q.empty()) {
        auto [cur, flow, p] = q.front();
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow, cur});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(MAXN);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;

        while (cur != s) {
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
    for (int t=1; t<=tc; t++) {
        int n; cin >> n;

        vector<int> arr(MAXN);
        adj.assign(MAXN, vector<int>());
        capacity.assign(MAXN, vector<int>(MAXN, 0));

        for (int i=1; i<=n; i++) {
            cin >> arr[i];
            adj[i + n].push_back(i);
            adj[i].push_back(i + n);

            capacity[i + n][i] += arr[i];
        }

        int m; cin >> m;
        for (int i=0, u, v, c; i<m; i++) {
            cin >> u >> v >> c;
            adj[u].push_back(v + n);
            adj[v + n].push_back(u);

            capacity[u][v + n] += c;
        }

        int source = 0, sink = 2 * n + 1;
        int b, d; cin >> b >> d;

        // source to entry points
        for (int i=0, u; i<b; i++) {
            cin >> u;
            adj[source].push_back(u + n);
            adj[u + n].push_back(source);

            capacity[source][u + n] = INF;
        }

        // last points to sink
        for (int i=0, u; i<d; i++) {
            cin >> u;
            adj[u].push_back(sink);
            adj[sink].push_back(u);

            capacity[u][sink] = INF;
        }

        int ans = maxflow(source, sink);
        cout << "Case " << t << ": " << ans << "\n";
    }

    return 0;
}