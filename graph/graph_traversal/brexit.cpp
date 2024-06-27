// https://open.kattis.com/problems/brexit

#include <bits/stdc++.h>
using namespace std;


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m, x, s;
    cin >> n >> m >> x >> s;

    vector<vector<int>> adj(n+1);
    vector<int> indegree(n+1, 0);
    vector<bool> leave(n+1, 0);

    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        indegree[a]++;
        indegree[b]++;
    }

    vector<int> original_indegree = indegree;

    queue<int> q;
    q.push(s);
    leave[s] = true;

    while (!q.empty())
    {
        int u = q.front(); q.pop();

        for (auto v : adj[u]) {
            if (leave[v]) continue;
            indegree[u]--;
            indegree[v]--;
            if (indegree[v]*2 <= original_indegree[v]) {
                q.push(v);
                leave[v] = true;
            }
        }
    }

    if (indegree[x] * 2 <= original_indegree[x]) cout << "leave\n";
    else cout << "stay\n";

    return 0;
}