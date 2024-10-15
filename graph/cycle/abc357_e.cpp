// https://atcoder.jp/contests/abc357/tasks/abc357_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> color, parent, adj, cnt, indegree;
vector<vector<int>> adj_t;
vector<bool> visited;
pair<int, int> cy = {-1, -1};

bool checkCycle(int u)
{
    color[u] = 1;

    int v = adj[u];
    if (color[v] == 0) {
        parent[v] = u;
        if (checkCycle(v)) {
            visited[u] = true;
            return true;
        }
    } else if (color[v] == 1 && !visited[v]) {
        cy = {v, u};
        visited[u] = true;
        return true;
    }

    color[u] = 2;
    visited[u] = true;
    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    adj.assign(n+1, 0);
    adj_t.resize(n+1);
    color.assign(n+1, 0);
    cnt.assign(n+1, 0);
    parent.assign(n+1, -1);
    indegree.assign(n+1, 0);
    visited.assign(n+1, false);

    for (int i=1; i<=n; i++) {
        int ax; cin >> ax;
        adj[i] = ax;
        adj_t[ax].push_back(i);
        indegree[ax]++;
    }

    queue<int> out_cycle;
    for (int i=1; i<=n; i++) {
        if (color[i] == 0) {
            bool rs = checkCycle(i);
            if (rs) {
                int st = cy.first;
                int c = 1;
                while (st != cy.second) {
                    c++;
                    if (indegree[st] > 1) out_cycle.push(st);
                    st = adj[st];
                }
                if (indegree[st] > 1) out_cycle.push(st);

                st = cy.first;
                while (st != cy.second) {
                    cnt[st] = c;
                    st = adj[st];
                }
                cnt[st] = c;
            }
            cy = {-1, -1};
        }
    }

    while (out_cycle.size()) {
        int u = out_cycle.front();
        out_cycle.pop();

        for (auto &v : adj_t[u]) {
            if (cnt[v] != 0) continue;
            cnt[v] = cnt[u] + 1;
            out_cycle.push(v);
        }
    }

    int ans = 0;
    for (int i=1; i<=n; i++) ans += cnt[i];

    cout << ans << "\n";

    return 0;
}