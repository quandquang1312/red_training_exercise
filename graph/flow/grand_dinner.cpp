// https://vjudge.net/problem/UVA-10249

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

int N;
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
    vector<int> parent(N);
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

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<int> teams(n), tables(m);
        bool possible = true;

        for (int i=0; i<n; i++) {
            cin >> teams[i];
            if (teams[i] > m) possible = false;
        }
        for (int i=0; i<m; i++) cin >> tables[i];

        int total_members = 0, total_cap = 0;
        for (int i=0; i<n; i++) total_members += teams[i];
        for (int i=0; i<m; i++) total_cap += tables[i];

        if (total_members > total_cap) possible = false;

        if (!possible) {
            cout << "0\n";
        } else {
            adj.assign(n + m + 2, vector<int>());
            capacity.assign(n + m + 2, vector<int>(n + m + 2, 0));

            int source = 0, sink = n + m + 2 - 1;
            N = sink + 1;

            // source -> teams (capacity = number of members)
            for (int i=1; i<=n; i++) {
                adj[source].push_back(i);
                adj[i].push_back(source);

                capacity[source][i] = teams[i - 1];
            }

            // teams -> tables (capacity = 1)
            for (int i=1; i<=n; i++) {
                for (int j=n+1; j<=n+m; j++) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);

                    capacity[i][j] = 1;
                }
            }

            // tables -> sink (capacity = number of seats)
            for (int i=n+1; i<=n+m; i++) {
                adj[i].push_back(sink);
                adj[sink].push_back(i);

                capacity[i][sink] = tables[i - n - 1];
            }

            int ans = maxflow(source, sink);
            if (ans != total_members) {
                cout << "0\n";
                continue;
            }

            cout << "1\n";

            // tracing - capacity[i][j] means used
            vector<vector<int>> trace(n);
            for (int i=1; i<=n; i++) {
                for (int j=n+1; j<=n+m; j++) {
                    if (capacity[i][j] == 0) {
                        trace[i-1].push_back(j - n);
                    }
                }
            }

            for (int i=0; i<n; i++) {
                for (int j=0; j<trace[i].size(); j++) {
                    if (j) cout << " ";
                    cout << trace[i][j];
                }
                cout << "\n";
            }
        }
    }

    return 0;
}