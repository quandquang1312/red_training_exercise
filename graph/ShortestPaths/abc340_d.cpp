// https://atcoder.jp/contests/abc340/tasks/abc340_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<vector<pair<int, int>>> adj(n+1);
    for (int i=1; i<=n; i++) {
        int a, b, x; cin >> a >> b >> x;
        if (i + 1 <= n) adj[i].push_back({a, i+1});
        adj[i].push_back({b, x});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    int st = 1;
    pq.push({0, st});
    vector<int> dist(n+1, 1e18);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &[w, v] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << dist[n] << endl;

    return 0;
}