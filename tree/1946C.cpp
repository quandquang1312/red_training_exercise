
// https://codeforces.com/contest/1946/problem/C

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n+1);

    for (int i=1; i<=n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto check = [=](int x) {
        int minimum_cut = 0;
        /*
        * dfs for calculate the size of subtree
        * that starts from node u
        */
        auto dfs = [&](auto self, int u, int v) -> int {
            int sz = 1; // the node u itself
            for (auto &e : adj[u]) {
                if (e == v) continue;
                sz += self(self, e, u); // for the subtree size of the node connects to u
            }

            if (sz >= x) {
                sz = 0, minimum_cut++; 
            }

            return sz;
        };

        int ans = dfs(dfs, 1, 1);

        // to check if the minimum_cut required to satisfy the minimum equal to x is less than k
        return (minimum_cut > k) ? true : false;
    };

    int l = 1, r = n;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (check(m)) l = m;
        else r = m - 1;
    }

    cout << l << endl;
}

int32_t main() {
    int tc; cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}