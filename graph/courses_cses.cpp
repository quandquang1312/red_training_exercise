// https://cses.fi/problemset/task/1679

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> rs;
vector<int> colors;
bool ans_isAcyclic;

bool checkCycle(int v)
{
    colors[v] = 1;

    for (int u : adj[v]) {
        if (colors[u] == 0) {
            if (checkCycle(u)) {
                ans_isAcyclic = true;
                return true;
            }
        } else if (colors[u] == 1) {
            ans_isAcyclic = true;
            return true;
        }
    }

    colors[v] = 2;
    return false;
}

bool isAcyclic(int n)
{
    colors.resize(n+1);

    for (int i=1; i<=n; i++) {
        if (colors[i] == 0 && checkCycle(i))
            break;
    }

    return ans_isAcyclic;
}

void dfs(int u)
{
    visited[u] = true;

    for (auto &e : adj[u]) {
        if (!visited[e]) dfs(e);
    }

    rs.push_back(u);
}

vector<int> topoSort(int n)
{
    visited.resize(n+1, false);
    rs.clear();

    for (int i=1; i<=n; i++) {
        if (!visited[i]) dfs(i);
    }

    reverse(rs.begin(), rs.end());
    return rs;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;
    adj.resize(n+1);

    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
    }

    if (isAcyclic(n)) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> ans = topoSort(n);
    for (auto &e : ans) {
        cout << e << " ";
    }
    cout << endl;

    return 0;
}