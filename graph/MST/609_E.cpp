// https://codeforces.com/problemset/problem/609/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

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

// LCA with tracing most heavy edges in a simple path u to v
class LCA {
public:
    int n, maxLog;
    vector<vector<pair<int,int>>> tree;
    vector<vector<int>> parent, maxEdge;
    vector<int> depth, dist;

    LCA(int _n) : n(_n) {
        tree.assign(n, {});
        depth.assign(n, 0);
        dist.assign(n, 0);

        maxLog = 32 - __builtin_clz(n);
        parent.assign(n, vector<int>(maxLog, -1));
        maxEdge.assign(n, vector<int>(maxLog, 0));
    }

    void addEdge(int u, int v, int w) {
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }

    void dfs(int u, int p = -1, int d = 0, int d2 = 0) {
        depth[u] = d;
        dist[u]  = d2;
        parent[u][0] = p;
        for (auto &ed : tree[u]) {
            int v = ed.first, w = ed.second;
            if (v == p) continue;
            maxEdge[v][0] = w;
            dfs(v, u, d+1, d2 + w);
        }
    }

    void buildSparseTable() {
        for (int j = 1; j < maxLog; ++j) {
            for (int i = 0; i < n; ++i) {
                int mid = parent[i][j-1];
                if (mid != -1) {
                    parent[i][j]  = parent[mid][j-1];
                    maxEdge[i][j] = max(maxEdge[i][j-1], maxEdge[mid][j-1]);
                }
            }
        }
    }

    void build(int root = 0) {
        dfs(root);
        buildSparseTable();
    }

    int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < maxLog; ++i)
            if (diff & (1 << i))
                u = parent[u][i];
        if (u == v) return u;
        for (int i = maxLog-1; i >= 0; --i) {
            if (parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return parent[u][0];
    }

    int liftMax(int u, int k) const {
        int best = 0;
        for (int i = 0; i < maxLog; ++i) {
            if (k & (1 << i)) {
                best = max(best, maxEdge[u][i]);
                u    = parent[u][i];
            }
        }
        return best;
    }

    int lca(int u, int v, int &most_heavy_edge) const {
        int w = lca(u, v);
        int mu = liftMax(u, depth[u] - depth[w]);
        int mv = liftMax(v, depth[v] - depth[w]);
        most_heavy_edge = max(mu, mv);
        return w;
    }

    int distance(int u, int v) const {
        int w = lca(u, v);
        return dist[u] + dist[v] - 2 * dist[w];
    }
};


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<tuple<int, int, int, int>> edges;

    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        edges.push_back({w, u, v, i});
    }

    sort(edges.begin(), edges.end());

    vector<bool> initialEdge(m, false);

    LCA lca(n + 1);

    auto calcMst = [&] (DSU &dsu, int ini_mst=0, int ii=-1) {
        int mst = ini_mst, cnt = (ii == -1 ? 0 : 1);
        for (auto &[w, u, v, i] : edges) {
            if (i == ii) continue;
            if (dsu.isSameSet(u, v)) continue;

            dsu.unionSet(u, v);
            lca.addEdge(u, v, w);
            if (ii == -1) initialEdge[i] = true;

            mst += w;
            cnt++;

            if (cnt == n - 1) break;
        }

        return mst;
    };

    DSU ini_dsu(n + 1);
    int mst = calcMst(ini_dsu, 0, -1);
    lca.build(1);

    vector<int> ans(m, 0);

    for (int i=0; i<m; i++) {
        auto &[w, u, v, ii] = edges[i];
        if (initialEdge[ii]) ans[ii] = mst;
        else {
            // find most heavy edges from u to v in the initial MST
            // remove the edges and and the edges from u to v
            int most_heavy_edge;
            int lca_uv = lca.lca(u, v, most_heavy_edge);
            // cout << u << " -> " << v << ": " << most_heavy_edge << "\n";
            int tmp_mst = mst - most_heavy_edge + w;
            ans[ii] = tmp_mst;
        }
    }

    for (int i=0; i<m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}