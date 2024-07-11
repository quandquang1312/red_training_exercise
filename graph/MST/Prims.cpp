#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> AL;
vector<int> taken;

priority_queue<pair<int, int>> pq;

void process(int u)
{
    taken[u] = 1;
    for (auto &[v, w] : AL[u]) {
        if (!taken[v])
            pq.push({-w, -v});
    }
}

void prims()
{
    long n, m;
    cin >> n >> m;
    AL.clear();
    AL.resize(n);

    for (int i=0; i<n; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        AL[u].push_back({v, w});
        AL[v].push_back({u, w});
    }

    taken.assign(n, 0);
    process(0);

    int mst_cost = 0, cnt = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        w = -w, u = -u;
        if (taken[u]) continue;

        mst_cost += w;
        process(u);
        cnt++;
        if (cnt == n - 1) break;
    }

    cout << mst_cost << endl;
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    return 0;
}