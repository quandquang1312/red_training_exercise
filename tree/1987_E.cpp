// https://codeforces.com/problemset/problem/1987/E

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

vector<int> volume;
vector<int> depth;
vector<int> parent;

void dfs(int u, int p, const vector<vector<int>>& adj, const vector<int>& arr) {
    depth[u] = depth[p] + 1;
    parent[u] = p;

    int sum_child = 0;
    int num_child = 0;

    for (auto &v : adj[u]) {
        if (v == p) continue;
        sum_child += arr[v];
        num_child += 1;
        dfs(v, u, adj, arr);
    }

    if (num_child == 0) volume[u] = INF;
    else volume[u] = sum_child - arr[u];
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n + 1);
        vector<vector<int>> adj(n + 1);

        volume.assign(n + 1, 0);
        depth.assign(n + 1, 0);
        parent.assign(n + 1, 0);

        for (int i=1; i<=n; i++) cin >> arr[i];
        for (int u=2, v; u<=n; u++) {
            cin >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0, adj, arr);

        int ans = 0;

        auto bfs = [&](int u) -> void {
            queue<int> q;

            q.push(u);

            while (!q.empty()) {
                int i = q.front();
                q.pop();

                for (auto &v : adj[i]) {
                    if (v == parent[i]) continue;
                    int diff = min(-volume[u], volume[v]);
                    if (diff > 0) {
                        volume[u] += diff;
                        volume[v] -= diff;
                        ans += (depth[v] - depth[u]) * diff;
                    }

                    q.push(v);
                }
            }

        };

        for (int u=n; u>=1; u--) {
            bfs(u);
        }

        cout << ans << "\n";
    }

    return 0;
}