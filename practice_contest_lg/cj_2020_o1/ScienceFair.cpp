// https://codejam.lge.com/problem/18767

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 15;
const int INF  = 1e18;

vector<vector<int>> adj, capacity;
vector<vector<bool>> adj_matrix;

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
        int n, m = 3; cin >> n;

        int source = 0, sink = m + 7 + 1;

        adj.assign(MAXN, vector<int>());
        capacity.assign(MAXN, vector<int>(MAXN, 0));
        adj_matrix.assign(MAXN, vector<bool>(MAXN, false));

        vector<int> gym(m + 1);
        cin >> gym[1] >> gym[2] >> gym[3];

        auto addEdge = [&] (int u, int v, int c=0) -> void {
            adj[u].push_back(v);
            adj[v].push_back(u);

            adj_matrix[u][v] = adj_matrix[v][u] = true;

            capacity[u][v] += c;
        };

        // source to gym
        for (int i=1; i<=m; i++) {
            addEdge(source, i, gym[i]);
        }

        vector<int> group(n + 1, 0);
        for (int i=0; i<m; i++) {
            int k; cin >> k;
            for (int j=0, v; j<k; j++) {
                cin >> v;
                group[v] |= (1 << i);
            }
        }

        vector<int> cnt_group(7 + 1, 0);
        vector<vector<int>> students(7 + 1);
        for (int i=1; i<=n; i++) {
            cnt_group[group[i]]++;
            students[group[i]].push_back(i);
        }

        // Edge gym to set
        for (int i=0; i<m; i++) {
            for (int j=1; j<=7; j++) {
                if ((1 << i) & j) addEdge(i + 1, j + m, n);
            }
       }

        // set to sink
        for (int i=1; i<=7; i++) {
            addEdge(i + m, sink, cnt_group[i]);
        }

        int ans = max_flow(source, sink, MAXN);
        cout << ans << "\n";

        vector<int> nextStudent(7 + 1, 0);
        for (int i=1; i<=3; i++) {
            for (int j=m+1; j<=m+7; j++) {
                if (capacity[i][j] != n && adj_matrix[i][j]) {
                    int amount = n - capacity[i][j];
                    for (int k=0; k<amount; k++) {
                        cout << students[j - m][nextStudent[j - m]] << " " << (char)('A' + (i - 1)) << "\n";
                        nextStudent[j - m]++; 
                    }
                }
            }
        } 
    }

    return 0;
}