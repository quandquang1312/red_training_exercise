// https://cses.fi/problemset/task/1668

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

    vector<vector<int>> adj(n+1);
    vector<int> color(n+1, 2);

    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bool isBipartitite = true;
    queue<int> q;
    for (int i=1; i<=n && isBipartitite; i++) {
        if (color[i] == 2) {
            color[i] = 0;
            q.push(i);

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (auto u : adj[v]) {
                    if (color[u] == 2) {
                        color[u] = 1 - color[v];
                        q.push(u);
                    } else if (color[u] == color[v]) {
                        isBipartitite = false;
                        break;
                    }
                }
            }
        }
    }

    if (!isBipartitite) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i=1; i<=n; i++)
            cout << color[i] + 1 << " ";
        cout << endl;
    }

    return 0;
}