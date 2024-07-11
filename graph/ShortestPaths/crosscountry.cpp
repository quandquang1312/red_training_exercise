// https://open.kattis.com/problems/crosscountry

#include <bits/stdc++.h>
using namespace std;

#define pqpair priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, s, d;
    cin >> n >> s >> d;
    // s--, d--;

    vector<int> dist(n, 1e9);
    dist[s] = 0;
    int mtr[n][n];

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> mtr[i][j];
        }
    }

    pqpair pq;
    pq.push({dist[s], s});

    while (!pq.empty())
    {
        auto [dd, u] = pq.top();
        pq.pop();

        for (int v=0; v<n; v++) {
            if (v == u) continue;
            if (dist[v] > dist[u] + mtr[u][v]) {
                dist[v] = dist[u] + mtr[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    // for (int i=0; i<n; i++) {
    //     cout << dist[d] << " ";
    // }
    cout << dist[d] << endl;

    return 0;
}