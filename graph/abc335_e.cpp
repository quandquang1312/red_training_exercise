// https://atcoder.jp/contests/abc335/tasks/abc335_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

class DSU {
private:
    vector<int> p, rank, setSize;
    int numSets;

public:
    DSU(int n) {
        p.assign(n, 0);
        for (int i=0; i<n; i++) p[i] = i;

        rank.assign(n, 0);
        setSize.assign(n, 1);
        numSets = n;
    }

    int findSet(int i) {
        if (p[i] == i) return i;
        return p[i] = findSet(p[i]);
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    int sizeOfSet(int i) {
        return setSize[findSet(i)];
    }

    int numOfSets() {
        return numSets;
    }

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;

        int x = findSet(i);
        int y = findSet(j);

        if (rank[x] > rank[y]) swap(x, y);

        p[x] = y;
        if (rank[x] == rank[y]) rank[y]++;

        setSize[y] += setSize[x];
        --numSets;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<int> arr(n + 1);
    for (int i=1; i<=n; i++) cin >> arr[i];

    DSU dsu(n + 1);

    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges(m);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        edges[i] = {u, v};

        if (arr[u] == arr[v]) dsu.unionSet(u, v);
    }

    for (auto &[u, v] : edges) {
        if (!dsu.isSameSet(u, v)) {
            int pu = dsu.findSet(u);
            int pv = dsu.findSet(v);
            if (arr[pu] < arr[pv]) adj[pu].push_back(pv);
            if (arr[pv] < arr[pu]) adj[pv].push_back(pu);
        }
    }

    int source = dsu.findSet(1);
    int dest   = dsu.findSet(n);

    vector<int> dp(n + 1, -1);
    vector<bool> reachable(n + 1, false), visited(n + 1, false);

    function<bool(int)> check = [&] (int u) -> bool {
        if (u == dest) return reachable[u] = true;
        visited[u] = true;

        for (auto &v : adj[u]) {
            if (!visited[v]) check(v);
            reachable[u] = reachable[u] | reachable[v];
        }

        return reachable[u];
    };

    check(source);

    function<int(int)> dfs = [&] (int u) -> int {
        if (dp[u] != -1)   return dp[u];
        if (!reachable[u]) return dp[u] = 0;

        int ans = 0;

        for (auto &v : adj[u]) {
            if (reachable[v])
                ans = max(ans, dfs(v));
        }

        return dp[u] = 1 + ans;
    };

    int ans = dfs(source);

    cout << ans << "\n";

    return 0;
}