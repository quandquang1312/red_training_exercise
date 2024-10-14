// https://atcoder.jp/contests/abc348/tasks/abc348_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = LLONG_MAX;

vector<int> sumC, F, C;
vector<vector<int>> adj;
int ans = INF;

void dfs(int u, int par) {
    sumC[u] = C[u];
    F[u] = 0;

    for (auto &v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
        sumC[u] += sumC[v];
        F[u] += sumC[v] + F[v];
    }
}

void rerooting(int u, int par) {
    ans = min(ans, F[u]);

    for (auto &v : adj[u]) {
        if (v == par) continue;
        
        // save origin
        int tmp_sm_u = sumC[u], tmp_f_u = F[u];
        int tmp_sm_v = sumC[v], tmp_f_v = F[v];

        // detach v from u
        sumC[u] -= sumC[v];
        F[u] -= (sumC[v] + F[v]);

        // attach v to u
        sumC[v] += sumC[u];
        F[v] += sumC[u] + F[u];

        rerooting(v, u);

        // backtrack
        sumC[u] = tmp_sm_u, F[u] = tmp_f_u;
        sumC[v] = tmp_sm_v, F[v] = tmp_f_v;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    sumC.assign(n + 1, 0);
    F.assign(n + 1, 0);
    C.assign(n + 1, 0);
    adj.resize(n + 1);

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i=1; i<=n; i++) cin >> C[i];

    dfs(1, 0);
    rerooting(1, 0);

    cout << ans << "\n";

    return 0;
}