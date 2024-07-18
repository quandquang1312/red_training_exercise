// https://atcoder.jp/contests/abc357/tasks/abc357_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> color, parent, adj, cnt, indegree;
pair<int, int> cy = {-1, -1};

bool checkCycle(int u)
{
    color[u] = 1;

    int v = adj[u];
    if (v == u) return false;
    if (color[v] == 0) {
        parent[v] = u;
        if (checkCycle(v))
            return true;
    } else if (color[v] == 1) {
        cy = {v, u};
        return true;
    }

    color[u] = 2;
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
    color.assign(n+1, 0);
    cnt.assign(n+1, 0);
    parent.assign(n+1, -1);
    indegree.assign(n+1, 0);

    for (int i=1; i<=n; i++) {
        int ax; cin >> ax;
        adj[i] = ax;
        if (ax == i) continue;
        indegree[ax]++;
    }

    queue<int> q;
    vector<bool> isIncycle(n+1, false);
    vector<vector<int>> cycles;
    for (int i=1; i<=n; i++) {
        cout << i << ": " << color[i] << endl;
        if (color[i] == 0) {
            if (checkCycle(i)) {
                vector<int> c;
                c.push_back(cy.first);

                int v = adj[cy.first];
                while (v != cy.first) {
                    c.push_back(v);
                    isIncycle[v] = true, v = adj[v];
                }
                cycles.push_back(c); 
            }
        }
    }

    for (auto &c : cycles) {
        for (auto &e : c) {
            cout << e << " ";
            cnt[e] = c.size();
        }
        cout << endl;
    }

    for (auto &c : cycles) {
        for (auto &e : c) {
            cnt[e] = c.size();
        }
    }

    color.assign(n+1, 0);
    for (int i=1; i<=n; i++) {
        cnt[i] = max(cnt[i], 1LL);
        if (indegree[i] == 0)
            color[i] = 1, q.push(i);
    }

    // cout << q.size() << endl;

    while (!q.empty())
    {
        int u = q.front(); q.pop();
        int v = adj[u];

        if (isIncycle[v] || color[v] == 1) continue;
        indegree[v]--;
        cnt[v] += cnt[u];

        if (indegree[v] == 0 && color[v] == 0 && isIncycle[v] == false)
            q.push(v), color[v] = 1;
    }

    // cout << "t: " << ttl_c << endl;

    int rs = 0;
    for (int i=1; i<=n; i++) {
        rs += cnt[i];
        cout << i << ": " << cnt[i] << "\n";
    }
    // cout << endl;

    cout << rs << endl;

    return 0;
}