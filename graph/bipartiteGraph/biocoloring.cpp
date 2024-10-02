// https://vjudge.net/problem/UVA-10004

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

    int n = 1;

    while ((cin >> n), n)
    {
        int l; cin >> l;
        vector<vector<int>> adj(n+1);
        vector<int> color(n+1, 2);
        
        int a, b;
        for (int i=0; i<l; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        queue<int> q;
        q.push(0);

        bool isBipartite = true;
        while (!q.empty() && isBipartite)
        {
            int v = q.front(); q.pop();

            for (auto &u : adj[v]) {
                if (color[u] == 2) {
                    color[u] = 1 - color[v];
                    q.push(u);
                } else if (color[u] == color[v]) {
                    isBipartite = false;
                    break;
                }
            }
        }

        cout << (isBipartite ? "BICOLORABLE.\n" : "NOT BICOLORABLE.\n");
    }

    return 0;
}