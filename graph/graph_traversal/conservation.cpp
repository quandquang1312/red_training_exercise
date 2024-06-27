// https://open.kattis.com/problems/conservation

#include <bits/stdc++.h>
using namespace std;
int n;

int solve(vector<vector<int>>& adj, vector<int>& indegree, vector<int>& labs, int pass)
{
    vector<int> topo;
    deque<int> q;

    for (int i=1; i<=n; i++) {
        if (indegree[i] == 0 && labs[i] == 1) if (pass == 1) q.push_front(i); else q.push_back(i);
        if (indegree[i] == 0 && labs[i] == 2) if (pass == 1) q.push_back(i); else q.push_front(i); 
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();

        topo.push_back(u);

        for (auto &v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0 && labs[v] == labs[u]) q.push_front(v);
            if (indegree[v] == 0 && labs[v] != labs[u]) q.push_back(v);
        }
    }

    int cnt = 0;
    for (int i=1; i<n; i++)
        if (labs[topo[i]] != labs[topo[i-1]]) cnt++;
    return cnt;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--)
    {
        int m; cin >> n >> m;

        vector<vector<int>> adj(n+1);
        vector<int> labs(n+1), indegree(n+1, 0), indegree2;

        for (int i=1; i<=n; i++) { cin >> labs[i];}

        int a, b;
        for (int i=0; i<m; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
            indegree[b]++;
        }

        indegree2 = indegree;

        cout << min(solve(adj, indegree, labs, 1), solve(adj, indegree2, labs, 2)) << endl;
    }

    return 0;
}