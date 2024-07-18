// https://cses.fi/problemset/task/1678

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> color, parent;
pair<int, int> cy = {-1, -1};

bool checkCycle(int u)
{
    color[u] = 1;

    for (auto &v : adj[u]) {
        if (color[v] == 0) {
            parent[v] = u;
            if (checkCycle(v))
                return true;
        } else if (color[v] == 1) {
            cy = {v, u};
            return true;
        }
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

    int n, m;
    cin >> n >> m;

    adj.resize(n+1);
    color.assign(n+1, 0);
    parent.assign(n+1, -1);

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i=1; i<=n; i++) {
        cout << i << ": ";
        for (auto v : adj[i])
            cout << v << " ";
        cout << endl;
    }

    for (int i=1; i<=n; i++) {
        if (color[i] == 0 && checkCycle(i)) break;
    }

    if (cy.first == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }


    vector<int> ans;
    ans.push_back(cy.first);
    for (int v = cy.second; v != cy.first; v = parent[v])
        ans.push_back(v);
    ans.push_back(cy.first);

    reverse(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (auto &e : ans) {
        cout << e << " ";
    } cout << endl;

    return 0;
}