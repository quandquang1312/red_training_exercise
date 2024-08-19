// https://cses.fi/problemset/task/1132/

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> dist, ans;
vector<vector<int>> adj;
int farthest;

void dfs(int node, int root, int d) {
    dist[node] = d;

    // determine the maximum distance from a node to two farthest nodes
    ans[node] = max(ans[node], dist[node]);


    for (auto &v : adj[node]) {
        if (root == v) continue;
        dfs(v, node, d + 1);
        if (dist[v] > dist[farthest]) farthest = v;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    
    adj.assign(n+1, vector<int>());
    dist.assign(n+1, 0);
    ans.assign(n+1, 0);

    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // find the first farthest node
    dfs(1, 1, 0);
    int tmp = farthest;
    farthest = 0;

    // calculate the distance of each node to the first farthest node
    // and find the second farthest node
    dfs(tmp, tmp, 0);
    tmp = farthest;
    farthest = 0;

    // calculate the distance of each node to the second farthest node
    dfs(tmp, tmp, 0);

    for (int i=1; i<=n; i++)
        cout << ans[i] << " ";
    cout << endl;

    return 0;
}