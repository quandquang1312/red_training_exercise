// https://cses.fi/problemset/task/1709

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

    int n; cin >> n;

    Dinic dinic(2 * n + 2);

    int source = 0, sink = 2 * n + 1;

    // Edges from source to rows (1...N)
    for (int u=1; u<=n; u++) {
        dinic.addEdge(source, u, 1);
    }

    // Edges from cols (N+1...N+N) to sink
    for (int u=n+1; u<=n+n; u++) {
        dinic.addEdge(u, sink, 1);
    }

    char x;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            cin >> x;
            if (x == 'o') dinic.addEdge(i, j + n, 1);
        }
    }

    dinic.maxFlow(source, sink);

    // Minimum Cut
    vector<pair<int, int>> ans;

    dinic.bfs(source, sink);

    for (int i=1; i<=n; i++) {
        if (dinic.level[i] < 0) ans.push_back({1, i});
    }

    for (int j=n+1; j<=n+n; j++) {
        if (dinic.level[j] >= 0) ans.push_back({2, j - n});
    }

    cout << ans.size() << "\n";
    for (auto &[tp, idx] : ans) {
        cout << tp << " " << idx << "\n";
    }


    return 0;
}