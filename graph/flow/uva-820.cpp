// https://vjudge.net/problem/UVA-820

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;
const int MAXN = 105;

vector<vector<int>> adj;
vector<vector<int>> capacity;

// Maximum Flow
int bfs(int s, int t, vector<int>& parent, tuple<int, int, int>& fl) {
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
                if (next == t) {
                    fl = {p, cur, new_flow};
                    return new_flow;
                }
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

    tuple<int, int, int> ans;

    while (new_flow = bfs(s, t, parent, ans)) {
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

    int n, tc = 1;
    while (cin >> n) {
        if (n == 0) break;
        int s, t, c; cin >> s >> t >> c;

        vector<tuple<int, int, int>> inputs(c);

        for (int i=0, u, v, w; i<c; i++) {
            cin >> u >> v >> w;
            inputs[i] = {u, v, w};
        }

        adj.assign(MAXN, vector<int>());
        capacity.assign(MAXN, vector<int>(MAXN, 0));

        for (auto &[u, v, w] : inputs) {
            adj[u].push_back(v);
            adj[v].push_back(u);

            capacity[u][v] += w;
            capacity[v][u] += w;
        }

        int ans = maxflow(s, t);
        cout << "Network " << tc++ << "\n";
        cout << "The bandwidth is " << ans << ".\n\n";
    }

    return 0;
}