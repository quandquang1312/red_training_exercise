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

    int n, mG, mH;
    cin >> n;

    vector<vector<bool>> G(n + 1, vector<bool>(n + 1, false));
    vector<vector<bool>> H = G;

    cin >> mG;
    for (int i=0, u, v; i<mG; i++) {
        cin >> u >> v;
        G[u][v] = true;
        G[v][u] = true;
    }

    cin >> mH;

    for (int i=0, u, v; i<mH; i++) {
        cin >> u >> v;
        H[u][v] = true;
        H[v][u] = true;
    }

    vector<vector<int>> cost(n + 1, vector<int>(n + 1, 0));
    for (int i=1; i<n; i++) {
        for (int j=i+1; j<=n; j++) {
            cin >> cost[i][j];
            cost[j][i] = cost[i][j];
        }
    }

    vector<int> per;
    for (int i=1; i<=n; i++) per.push_back(i);

    int ans = 1e9;
    do {
        set<pair<int, int>> rm;
        for (int i=1; i<=n; i++) {
            for (int j=2; j<=n; j++) {
                int u = per[i-1], v = per[j-1];

                if (G[i][j] + H[u][v] == 1) {
                    rm.insert({min(u, v), max(u, v)});
                }
            }
        }

        int curr = 0;
        for (auto [u, v] : rm) {
            curr += cost[u][v];
        }

        ans = min(ans, curr);

    } while (next_permutation(per.begin(), per.end()));

    cout << ans << '\n';

    return 0;
}