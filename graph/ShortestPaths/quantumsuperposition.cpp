// https://open.kattis.com/problems/quantumsuperposition

#include <bits/stdc++.h>
using namespace std;

int n1, n2, m1, m2;
vector<int> indegree_1, indegree_2;
vector<vector<int>> adj_1, adj_2;
vector<set<int>> dp_1, dp_2;
set<int> ans;

void bfs(int n, vector<vector<int>>& adj, vector<int>& indegree, vector<set<int>>& dp) {
    queue<int> q;
    q.push(1);
    dp[1].insert(0);

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        for (auto &v : adj[u]) {
            for (auto &d : dp[u]) {
                dp[v].insert(d + 1);
            }

            // only consider the vertice v when all of its u is done
            // to calculate the dp above precisely 
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n1 >> n2 >> m1 >> m2;

    adj_1.resize(n1 + 1);
    adj_2.resize(n2 + 1);

    dp_1.resize(n1 + 1);
    dp_2.resize(n2 + 1);

    indegree_1.resize(n1 + 1, 0);
    indegree_2.resize(n2 + 1, 0);

    for (int i=0, u, v; i<m1; i++) {
        cin >> u >> v;
        adj_1[u].push_back(v);
        indegree_1[v]++;
    }

    for (int i=0, u, v; i<m2; i++) {
        cin >> u >> v;
        adj_2[u].push_back(v);
        indegree_2[v]++;
    }

    bfs(n1, adj_1, indegree_1, dp_1);
    bfs(n2, adj_2, indegree_2, dp_2);

    for (auto &e : dp_1[n1]) {
        for (auto &d : dp_2[n2]) {
            ans.insert(e + d);
        }
    }

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        bool fl = (ans.find(x) != ans.end());

        cout << (fl ? "Yes\n" : "No\n");
    }

    return 0;
}