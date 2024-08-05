// https://usaco.org/index.php?page=viewproblem2&cpid=968

#include <bits/stdc++.h>
using namespace std;

bool dfs_sub1(int u, int par, int tar, bool getIt, int br, vector<vector<int>>& adj, vector<int>& breeds) {
    if (tar == u) {
        if (br == breeds[u] || getIt) return true;
        return false;
    }
    if (adj[u].size() == 1 && par != 0) return false;

    getIt |= (br == breeds[u]);

    int ans = false;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        ans |= dfs_sub1(v, u, tar, getIt, br, adj, breeds);
    }

    return ans;
}

void dfs(int u, int par, int c, vector<vector<int>>& adj, vector<int>& breeds, vector<int>& marked) {
    marked[u] = c;
    for (auto &v : adj[u]) {
        if (v == par) continue;
        if (breeds[v] == breeds[u] && marked[v] == 0) {
            dfs(v, u, c, adj, breeds, marked);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #if 1
        freopen("milkvisits.in", "r", stdin);
        freopen("milkvisits.out", "w", stdout);
    #endif

    int n, m, u, v;
    cin >> n >> m;

    vector<int> breeds(n+1);
    vector<vector<int>> adj(n+1);
    char ch;
    for (int i=0; i<n; i++) {
        cin >> ch;
        breeds[i+1] = (ch == 'H');
    }
    for (int i=0; i<n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n <= 2*1e3 && m <= 2*1e3) {
        while (m--) {
            int u, v;
            cin >> u >> v >> ch;
            cout << (dfs_sub1(u, 0, v, false, (ch == 'H'), adj, breeds));
        }
    } else {
        vector<int> marked(n+1, 0);
        int c = 1;
        for (int i=1; i<=n; i++) {
            if (marked[i] == 0) {
                dfs(i, 0, c, adj, breeds, marked);
                c++;
            }
        }

        while (m--) {
            int u, v;
            cin >> u >> v >> ch;
            if (marked[u] == marked[v]) cout << ((ch == 'H') == breeds[u]);
            else cout << '1';
        }
    }

    cout << '\n';

    return 0;
}