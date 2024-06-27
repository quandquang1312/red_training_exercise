// https://open.kattis.com/problems/wheresmyinternet

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
int n, m, cnt;

void dfs(int v, int parent)
{
    if (visited[v]) return;
    visited[v] = true;
    cnt++;

    for (auto &u : adj[v]) {
        if (u == parent) continue;
        dfs(u, v);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n >> m;
    adj.resize(n+1);
    visited.resize(n+1, 0);
    cnt = 0;

    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 1);

    if (cnt == n) {
        cout << "Connected\n";
        return 0;
    }

    for (int i=1; i<=n; i++) {
        if (!visited[i])
            cout << i << " ";
    }

    cout << endl;


    return 0;
}