// https://cses.fi/problemset/task/1711

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> in;

// Max Flow Edmons-Karp
int max_flow(vector<vector<int>> adj, vector<vector<int>> capacity,
                   int source, int sink) {
    int n = adj.size();
    vector<int> parent(n, -1);
    auto reachable = [&]() -> bool {
        queue<int> q;
        q.push(source);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int son : adj[node]) {
                int w = capacity[node][son];
                if (w <= 0 || parent[son] != -1)
                    continue;
                parent[son] = node;
                q.push(son);
            }
        }
        return parent[sink] != -1;
    };

    int flow = 0;
    while (reachable()) {
        int node = sink;
        int curr_flow = LLONG_MAX;
        while (node != source)
        {
            curr_flow = min(curr_flow, capacity[parent[node]][node]);
            node = parent[node];
        }
        node = sink;
        while (node != source)
        {
            capacity[parent[node]][node] -= curr_flow;
            capacity[node][parent[node]] += curr_flow;
            node = parent[node];
        }
        flow += curr_flow;
        fill(parent.begin(), parent.end(), -1);
    }

    return flow;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    vector<vector<int>> capacity(n, vector<int>(n));
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] += 1;
    }

    cout << max_flow(adj, capacity, 0, n - 1) << endl;
}
