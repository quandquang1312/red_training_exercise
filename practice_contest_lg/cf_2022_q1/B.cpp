// https://codejam.lge.com/problem/24436

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e12
#define MAXN 1e5

vector<int> getNei(int u) {
    if (u == 0) {
        vector<int> rs {10, 20, 30, 40, 50, 60, 70, 80, 90, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        return rs;
    }

    int sz = to_string(u).size();

    vector<int> rs;
    for (int i=0; i<sz; i++) {
        if (to_string(u)[i] != '9') rs.push_back(u + pow(10, sz - i - 1));
        if (to_string(u)[i] != '0') if (!(i == 0 && to_string(u)[i] == '1')) rs.push_back(u - pow(10, sz - i - 1));
    }

    return rs;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    // vector<int> ts = getNei(19);
    // for (auto &e : ts) {
    //     cout << e << " ";
    // } cout << endl;

    int tc; cin >> tc;
    while (tc--) {
        int l, k, x, y;
        cin >> l >> k >> x >> y;

        int n = pow(10, l);

        vector<vector<int>> adj(n);
        vector<int> dist(MAXN, INF);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, x});
        dist[x] = 0;

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            vector<int> adj = getNei(u);
            for (auto &v : adj) {
                if (dist[v] > d + 1) {
                    dist[v] = d + 1;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[y] == INF) {
            cout << "NO\n";
        } else {
            cout << "Implementing... " << dist[y] << "\n";
        }
    }

    return 0;
}