// https://atcoder.jp/contests/abc362/tasks/abc362_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> AL(n+1);
    vector<int> arr(n+1);
    for (int i=1; i<=n; i++) cin >> arr[i];
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        AL[u].push_back({w, v});
        AL[v].push_back({w, u});
    }

    vector<int> dist(n+1, LLONG_MAX);
    dist[1] = arr[1];

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[1], 1});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &[w, v] : AL[u]) {
            if (dist[v] > w + d + arr[v]) {
                dist[v] = w + d + arr[v];
                pq.push({dist[v], v});
            }
        }
    }

    for (int i=2; i<=n; i++) {
        cout << dist[i] << " ";
    } cout << endl;

    return 0;
}