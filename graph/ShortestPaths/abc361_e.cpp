// https://atcoder.jp/contests/abc361/tasks/abc361_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

pair<int, int> diameter(int s, vector<vector<pair<int, int>>>& adj) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(adj.size(), INF);
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [w, v] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    int farthest = 0, pos = -1;
    for (int i=1; i<adj.size(); i++) {
        if (farthest < dist[i]) {
            farthest = dist[i];
            pos = i;
        }
    }

    return {pos, farthest};
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<vector<pair<int, int>>> adj(n+1);

    int sum_c = 0;
    for (int i=1; i<n; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({c, v});
        adj[v].push_back({c, u});
        sum_c += c;
    }

    auto [pos, _] = diameter(1, adj);
    pair<int, int> ans = diameter(pos, adj);

    cout << 2*sum_c - ans.second << endl;

    return 0;
}