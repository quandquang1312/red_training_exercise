#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, topos;
vector<int> indegree;
vector<bool> visited;


void backtrack(vector<int>& res)
{
    for (int i=1; i<=n; i++) {
        if (indegree[i] == 0 && !visited[i])
        {
            for (auto u : adj[i])
                indegree[u]--;

            res.push_back(i);
            visited[i] = true;
            backtrack(res);

            visited[i] = false;
            res.pop_back();

            for (auto u : adj[i])
                indegree[u]++;
        }
    }

    if (res.size() == n) topos.push_back(res);
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
    indegree.resize(n+1, 0);

    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        indegree[b]++;
    }

    vector<int> res;
    visited.resize(n+1,0);
    backtrack(res);

    for (auto topo : topos) {
        for (auto &v : topo) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}