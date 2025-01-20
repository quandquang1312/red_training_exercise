#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<string> grid(n);

        vector<vector<int>> graph(n + 1);
        for (int i=0; i<n; i++) cin >> grid[i];

        vector<int> indegree(n + 1, 0);
        for (int i=0; i<n; i++) {
            for (int j=i; j<n; j++) {
                if (grid[i][j] == '1') {
                    int u = i + 1, v = j + 1;
                    if (u < v) {
                        graph[u].push_back(v);
                        indegree[v]++;
                    } else {
                        graph[v].push_back(u);
                        indegree[u]++;
                    }
                }
            }
        }

        priority_queue<int> q;
        for (int i=1; i<=n; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> ans;
        while (!q.empty()) {
            int u = q.top();
            q.pop();

            ans.push_back(u);

            for (auto &v : graph[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        for (int i=0; i<ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";

    }

    return 0;
}