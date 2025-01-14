// https://atcoder.jp/contests/abc324/tasks/abc324_f

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

    int n, m; cin >> n >> m;

    vector<vector<tuple<int, int, int>>> adj(n + 1);
    for (int i=0; i<m; i++) {
        int u, v, b, c;
        cin >> u >> v >> b >> c;
        adj[u].push_back({v, b, c});
    }

    vector<double> dp(n + 1);

    // find the largest x (P[n]) where sum(b_i) / sum(c_i) >= x
    // : sum(b_i) >= x * sum(c_i)
    // : sum(b_i) - x * sum(c_i) >= 0
    auto check = [&](double x) -> bool {
        vector<double> P(n + 1, -1e18);
        P[1] = 0.0;

        for (int u=1; u<=n; u++) {
            for (auto &[v, b, c] : adj[u]) {
                P[v] = max(P[v], P[u] + ((b * 1.0) - (c * 1.0) * x));
            }
        }

        return P[n] >= 0;
    };

    double l = 0.0, r = 1e18;
    while ((r - l >= 1e-10)) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    printf("%.9f\n", l);

    return 0;
}