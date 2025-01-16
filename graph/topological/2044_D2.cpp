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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> indegree(n, 0);
        vector<int> adj(n), dist(n, 1);

        for (int u=0, v; u<n; u++) {
            cin >> v;
            v--;

            indegree[v]++;
            adj[u] = v;
        }

        queue<int> q;

        for (int i=0; i<n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        if (q.size() == 0) {
            cout << "2\n";
        } else {
            int ans = 2;
            while (!q.empty()) {
                int u = q.front();
                q.pop();

                int v = adj[u];
                indegree[v]--;
                dist[v] += dist[u];

                if (indegree[v] == 0) {
                    ans = max(ans, dist[v] + 1);
                    q.push(v);
                }
            }

            cout << ans + 1 << "\n";
        }
    }

    return 0;
}