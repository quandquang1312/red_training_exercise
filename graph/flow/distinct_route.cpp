// https://cses.fi/problemset/task/1711
 
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
const int INF = 1e18;
 
int n;
vector<vector<int>> adj, capacity;
 
// Maximum Flow
int bfs(int source, int stink, vector<int>& parent) {
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
                if (v == stink) return new_flow;
                q.push({v, new_flow});
            }
        } 
    }
 
    return 0;
}
 
int max_flow(int source, int stink, vector<vector<int>>& paths) {
    int flow = 0;
    vector<int> parent(n + 1);
    int new_flow;
 
    paths.clear();
    while (new_flow = bfs(source, stink, parent)) {
        vector<int> path {stink};
        flow += new_flow;
        int cur = stink;
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        paths.push_back(path);
    }
 
    return flow;
}
 
void preprocess(int n) {
    adj.assign(n + 1, vector<int>());
    capacity.assign(n + 1, vector<int>(n + 1, 0));
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
 
    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif
 
    int m; cin >> n >> m;
    
    preprocess(n);
    
    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += 1;
    }
    vector<vector<int>> sol;
    int ans = max_flow(1, n, sol);
    cout << ans << endl;
 
    for (auto &e : sol) {
        cout << e.size() << "\n";
        for (auto &cur : e) {
            cout << cur << " ";
        } cout << endl;
    }
 
    return 0;
}
