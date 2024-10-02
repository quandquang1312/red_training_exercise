// https://codeforces.com/contest/1296/problem/E1

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> color;
bool bipartite = true;

// Bipartite using dfs
void dfs(int u, int c) {
    color[u] = c;
    for (auto v : adj[u]) {
        if (color[v] == -1)
            dfs(v, c ^ 1);
        else if (color[v] == color[u])
            bipartite = false;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    adj.resize(n);
    color.assign(n, -1);
    vector<pair<char, int>> str(n);

    for (int i=0; i<n; i++) {
        cin >> str[i].first;
        str[i].second = i;
    }

    for (int d=0; d<n-1; d++) {
        for (int i=0; i<n-1; i++) {
            if (str[i].first > str[i+1].first) {
                int u = str[i].second, v = str[i+1].second;
                adj[u].push_back(v);
                adj[v].push_back(u);
                swap(str[i], str[i + 1]);
            }
        }
    }

    for (int i=0; i<n; i++) {
        if (color[i] == -1) dfs(i, 0);
    }

    if (!bipartite) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i=0; i<n; i++) cout << color[i];
        cout << "\n";
    }

    return 0;
}