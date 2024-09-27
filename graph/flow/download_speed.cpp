// https://cses.fi/problemset/task/1694
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 100;
const int INF = 1e15;

// Max Flow Push Relabel
class MaxFlow {
private:
    int n, source, sink;
    int capacity[MAXN + 1][MAXN + 1];
    int flow[MAXN + 1][MAXN + 1];
    vector<int> excess, height, next_son;
    queue<int> excess_vertexes;

    void relabel(int u) {
        int d = INF;
        for (int v = 1; v <= n; v++) {
            if (capacity[u][v] > flow[u][v]) d = min(d, height[v]);
        }

        if (d < INF) height[u] = d + 1;
    }

    void push(int u, int v) {
        int d = min(excess[u], capacity[u][v] - flow[u][v]);
        flow[u][v] += d;
        flow[v][u] -= d;
        excess[u] -= d;
        excess[v] += d;
        if (d && excess[v] == d) excess_vertexes.push(v); 
    }

    void discharge(int u) {
        while (excess[u] > 0) {
            if (next_son[u] <= n) {
                int v = next_son[u];
                if (capacity[u][v] > flow[u][v] && height[u] > height[v]) push(u, v);
                else next_son[u]++;
            } else {
                relabel(u);
                next_son[u] = 1;
            }
        }
    }

public:
    MaxFlow(int nodes) : n(nodes) {
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
        excess.resize(n + 1);
        height.resize(n + 1);
        next_son.resize(n + 1);
    }

    void addEdge(int u, int v, int cap) {
        capacity[u][v] += cap;
    }

    int maxFlow(int s, int t) {
        source = s;
        sink = t;
        height[source] = n;
        excess[source] = INF;

        for (int i = 1; i <= n; i++) {
            if (i == source) continue;
            push(source, i);
        }

        while (!excess_vertexes.empty()) {
            int node = excess_vertexes.front();
            excess_vertexes.pop();
            if (node != source && node != sink) {
                discharge(node);
            }
        }

        int max_flow = 0;
        for (int node = 1; node <= n; node++) {
            max_flow += flow[node][sink];
        }
        return max_flow;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    MaxFlow graph(n);
    for (int i=0, u, v, c; i<m; i++) {
        cin >> u >> v >> c;
        graph.addEdge(u, v, c);
    };

    int ans = graph.maxFlow(1, n);
    cout << ans << "\n";

    return 0;
}
