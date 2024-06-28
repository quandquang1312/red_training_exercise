// https://vjudge.net/problem/UVA-10505

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;

    while (tc--)
    {
        int n; cin >> n;

        vector<set<int>> adj(210);
        vector<int> color(n+1, 2);

        for (int i=1; i<=n; i++) {
            int sz, v; cin >> sz;
            while (sz--) {
                cin >> v;
                adj[i].insert(v);
                adj[v].insert(i);
            }
        }

        int ans = 0;
        for (int i=1; i<=n; i++)
        {
            if (color[i] != 2) continue;
            bool isBipartite = true;

            queue<int> q;
            q.push(i);

            color[i] = 1;
            int cnt[2] = {0, 0};

            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                cnt[color[u]]++;

                for (auto &v : adj[u]) {
                    if (color[v] == 2) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        isBipartite = false;
                    }
                }
            }

            while (!q.empty()) q.pop();

            if (isBipartite) ans += max(cnt[0], cnt[1]);
        }

        cout << ans << endl;
    }

    return 0;
}