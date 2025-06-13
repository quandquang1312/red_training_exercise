// https://codeforces.com/problemset/problem/1572/A

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<vector<int>> adj(n + 1);
        vector<int> indegree(n + 1, 0);

        for (int i=1, k, x; i<=n; i++) {
            cin >> k;
            while (k--) {
                cin >> x;
                adj[x].push_back(i);
                indegree[i]++;
            }
        }

        for (int i=1; i<=n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }

        priority_queue<int> q;
        set<int> st;
        for (int i=1; i<=n; i++) {
            if (indegree[i] == 0) q.push(-i);
        }
        
        bool possible = (q.size() != 0);

        int cnt = 0;
        while (!q.empty()) {
            int u = q.top(); q.pop();
            u = -u;

            for (auto &v : adj[u]) {
                indegree[v]--;

                if (indegree[v] == 0) {
                    if (v < u) st.insert(v);
                    else q.push(-v);
                }
            }

            if (q.empty()) {
                for (auto &e : st) q.push(-e);
                st.clear();
                cnt++;
            }
        }

        for (int i=1; i<=n; i++) {
            if (indegree[i]) possible = false;
        }

        cout << (possible ? cnt : -1) << "\n";
    }

    return 0;
}