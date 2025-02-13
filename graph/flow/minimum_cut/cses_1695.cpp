// https://cses.fi/problemset/task/1695

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

struct Edge {
    int to, rev, cap;
};
 
class Dinic {
public:
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;
 
    Dinic(int n): n(n), adj(n), level(n), ptr(n) {}
 
    void addEdge(int u, int v, int cap) {
        Edge a = {v, (int) adj[v].size(), cap};
        Edge b = {u, (int) adj[u].size(), 0};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }
 
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);

        level[s] = 0;
        queue<int> q;
        q.push(s);

        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto &e : adj[u]) {
                if(level[e.to] < 0 && e.cap) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[t] >= 0;
    }
 
    int dfs(int u, int t, int flow) {
        if(!flow) return 0;
        if(u == t) return flow;

        for(int &i = ptr[u]; i < (int)adj[u].size(); i++){
            Edge &e = adj[u][i];
            if(level[e.to] != level[u] + 1 || e.cap == 0) continue;
            int pushed = dfs(e.to, t, min(flow, e.cap));
            if(pushed) {
                e.cap -= pushed;
                adj[e.to][e.rev].cap += pushed;
                return pushed;
            }
        }

        return 0;
    }
 
    int maxFlow(int s, int t) {
        int flow = 0;

        while(bfs(s,t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(s,t,INT_MAX))
                flow += pushed;
        }

        return flow;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<pair<int, int>> orig;
    vector<pair<int, int>> edges;

    Dinic dinic(n + 1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;

        orig.push_back({u, v});

        dinic.addEdge(u, v, 1);
        dinic.addEdge(v, u, 1);
    }

    int flow = dinic.maxFlow(1, n);
    vector<bool> visited(n + 1, false);

    function<void(int)> markReach = [&] (int u) -> void {
        visited[u] = true;

        auto adj = dinic.adj;

        for (auto &v : adj[u]) {
            if (!visited[v.to] && v.cap > 0)
                markReach(v.to);
        }
    };

    markReach(1);

    vector<pair<int, int>> removeEdges;
    for (auto &[u, v] : orig) {
        if ((visited[u] && !visited[v]) || (!visited[u] && visited[v])) {
            removeEdges.push_back({u, v});
        }
    }

    cout << removeEdges.size() << "\n";
    for (auto &[u, v] : removeEdges) {
        cout << u << " " << v << "\n";
    }

    return 0;
}