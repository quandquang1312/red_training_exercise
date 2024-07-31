// https://codejam.lge.com/contest/problem/1306/3

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m, p, k;
        cin >> n >> m >> p >> k;

        vector<vector<int>> adj(n+1), adj_trans(n+1);
        vector<int> c(n+1), indegree(n+1, 0), indegree_original;
        for (int i=1; i<=n; i++) cin >> c[i];
        for (int i=0; i<m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj_trans[v].push_back(u);
            indegree[v]++;
        }

        indegree_original = indegree;

        vector<int> topo;
        queue<int> q;
        int lst = 1;
        for (int i=1; i<=n; i++) if (indegree[i] == 0) q.push(i);

        while (!q.empty()) {
            int u = q.front();
            cout << u << " ";
            q.pop();
            topo.push_back(u);

            for (auto &v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) q.push(v);
            }
        }

        vector<int> ans(n+1, 0);
        int ttl = 0, cnt = topo.size();
        for (auto &u : topo) {
            // cout << u << " ";
            if (indegree_original[u] == 0) {
                // cout << u << ": " << c[u] << '\n';
                ans[u] = c[u]; 
            } else {
                // cout << u << ": I ";

                int max_day = -1;
                for (auto &v : adj_trans[u]) {
                    // cout << v << " ";
                    max_day = max(max_day, ans[v]);
                } 
                // cout << endl;

                // cout << u << ": m " << max_day << endl;
                if ((max_day % p) < c[u]) {
                    ans[u] = (max_day % MOD) + (c[u] - (max_day % p)) % MOD;
                    ans[u] %= MOD;
                } else {
                    ans[u] = ((max_day/p + 1) % MOD * p % MOD) % MOD + c[u];
                    ans[u] %= MOD;
                }

                // if (indegree_original[u] == 1) {
                //     int par = adj_trans[u][0];
                //     if (c[par] < c[u]) ans[u] = c[u];
                //     else ans[u] = c[u] + p;
                //     // cout << " - D " << ans[u] << endl;
                // }

                // cout << u << ": " << ans[u] << endl;
            }

            // printf("%d - %d, %d, %d -> %d\n", u, ans[u], lst, cnt, (min(ans[u], k + 1) - lst) * cnt);

            int a = (min(ans[u], k + 1) % MOD) - (lst % MOD);
            // int b = cnt;
            ttl += (a % MOD) * (cnt % MOD);
            ttl %= MOD;
            // ttl += (k + 1 - ans[u]);
            lst = ans[u] % MOD;
            cnt--;
        }
        cout << endl;
        for (int i=1; i<=n; i++) {
            if (indegree[i] != 0) {
                ttl += (k % MOD);
                ttl %= MOD;
            }
        }

        cout << ttl << endl;
    }

    return 0;
}