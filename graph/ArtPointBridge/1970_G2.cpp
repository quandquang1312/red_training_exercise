// https://codeforces.com/contest/1970/problem/G2

#include <bits/stdc++.h>
using namespace std;

#define int long long

int sqr(int x) {
    return x * x;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m, c;
        cin >> n >> m >> c;

        int timer = 0;
        vector<vector<int>> adj(n + 1);
        vector<int> parent(n + 1, -1);
        vector<int> dfs_low(n + 1, 0), dfs_num(n + 1, -1);
        vector<pair<int, int>> bridges;
        vector<int> visited(n + 1, false);

        for (int i=0, u, v; i<m; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        function<int(int)> dfs = [&] (int u) -> int {
            dfs_num[u] = dfs_low[u] = timer++;

            int res = 1;

            for (auto &v : adj[u]) {
                if (dfs_num[v] == -1) {
                    parent[v] = u;

                    res += dfs(v);

                    if (dfs_low[v] > dfs_num[u]) bridges.push_back({u, v});
                    dfs_low[u] = min(dfs_low[u], dfs_low[v]);
                } else if (v != parent[u]) {
                    dfs_low[u] = min(dfs_low[u], dfs_num[v]);
                }
            }

            return res;
        };

        function<int(int)> dfs2 = [&] (int u) -> int {
            if (visited[u]) return 0;
            visited[u] = true;

            int sz = 1;

            for (auto &v : adj[u]) {
                if (!visited[v]) {
                    sz += dfs2(v);
                    visited[v] = true;
                }
            }

            return sz;
        };

        vector<int> sizeOfCC;
        for (int i=1; i<=n; i++) {
            if (dfs_num[i] == -1) {
                int sz = dfs(i);
                sizeOfCC.push_back(sz);
            }
        }

        // cout << "bridges size: " << bridges.size() << "\n";

        if (bridges.size() == 0 && sizeOfCC.size() == 1) {
            cout << "-1\n";
            continue;
        }

        /*
        - if one cc is a whole complex
        */
        int ans = 1e18;
        int cc = sizeOfCC.size();
        for (auto& e : sizeOfCC) {
            int k = n - e;
            int cur = sqr(e) + sqr(k) + (cc - 1) * c;
            // cout << "ans: " << e << "^2 + " << k << "^2 + (" << e - 1 << " * " << c << ") = " << cur << "\n";
            ans = min(ans, cur);
        }

        /*
        - if some cc is a whole complex, and the rest is the other complex
        */

        vector<int> presum(cc + 1, 0);
        for (int i=0; i<cc; i++) {
            presum[i + 1] += presum[i] + sizeOfCC[i];
        }

        map<int, int> mp;
        for (int i=0; i<cc; i++) {
            for (int j=1; j<=presum[i + 1]; j++) {
                if (mp.find(presum[i] - j) != mp.end()) {
                    // found subarrays whose sum is j
                    ans = min(ans, sqr(j) + sqr(n - j) + (cc - 1) * c);
                }

                mp[presum[i]]++;
            }
        }

        /*
        bridges:
            a, b: size of the connected component after removing that bridge
            case 1: a will merge with some of the other CCs to form complex 1
                  b will merge with the rest of the CCs to form complex 2
            to minimize complex1^2 + complex2^2 will have to minimize the difference between complex1 and complex2
            so we add from the largest to the smallest and finally compute the answer in that case


            case 2: a will merge the the rest of the CCs
                  b will be the whole complex
                  or vice versa, a will be the whole complex

            k: n - (a + b)

            ans = min(ans, a^2 + (k+b)^2);
            ans = min(ans, b^2 + (k+a)^2);


        */

        for (int i=0; i<bridges.size(); i++) {

            auto &[u, v] = bridges[i];

            visited[v] = true;
            int size_u = dfs2(u);
            visited[v] = false;
            int size_v = dfs2(v);


            int k = n - (size_u + size_v); 
            ans = min(ans, sqr(size_u) + sqr(k + size_v) + (cc - 1) * c);
            ans = min(ans, sqr(size_v) + sqr(k + size_u) + (cc - 1) * c);

            vector<int> tmp;
            bool added = false;
            for (int j=0; j<cc; j++) {
                if (sizeOfCC[j] == size_u + size_v) {
                    if (!added) {
                        tmp.push_back(size_u);
                        tmp.push_back(size_v);
                        added = true;
                    } else {
                        tmp.push_back(sizeOfCC[j]);
                    }
                } else {
                    tmp.push_back(sizeOfCC[j]);
                }
            }

            sort(tmp.rbegin(), tmp.rend());

            int left = 0, right = 0;
            for (int j=0; j<tmp.size(); j++) {
                if (left < right) left += tmp[j];
                else right += tmp[j];
            }

            ans = min(ans, sqr(left) + sqr(right) + (cc - 1) * c);

            visited.assign(n + 1, false);
        }

        cout << ans << "\n";

    }

    return 0;
}