// https://usaco.org/index.php?page=viewproblem2&cpid=576

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100100

vector<vector<int>> adj;
vector<int> startIdx, endIdx;
int n, q, arr[MAXN], diff[MAXN], timer;

void update(int l, int r, int vl) {
    diff[l] += vl;
    diff[r] -= vl;
}

void apply_update()
{
    for (int i=0; i<=n*2; i++) diff[i] += diff[i-1];
}

void euler_tour(int at, int prev) {
    startIdx[at] = timer++;
    for (int v : adj[at]) {
        if (v != prev) { euler_tour(v, at); }
    }
    endIdx[at] = timer++;
}

struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visited;
    int n;

    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(adj, root);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : adj[node]) {
            if (!visited[to]) {
                dfs(adj, to, h + 1);
                euler.push_back(node);
            }
        }
    }

    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #else
        freopen("maxflow.in", "r", stdin);
        freopen("maxflow.in", "w", stdout);
    #endif

    cin >> n >> q;

    adj.resize(n + 1);
    startIdx.assign(n + 1, 0);
    endIdx.assign(n + 1, 0);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    euler_tour(1, 0);
    for (int i=1; i<=n; i++) {
        cout << startIdx[i] << " = " << endIdx[i] << '\n';
    }

    LCA mLCA(adj, 1);

    auto getPos = [&](int u, int v) -> pair<int, int> {
        if (startIdx[u] > startIdx[v]) return {v, u};
        return {u,v};
    };

    while (q--) {
        int u, v;
        cin >> u >> v;
        
        int w = mLCA.lca(u, v);

        auto [a, b] = getPos(u, w);
        auto [c, d] = getPos(v, w);

        update(startIdx[a], startIdx[v], 1);
    }

    apply_update();


    return 0;
}