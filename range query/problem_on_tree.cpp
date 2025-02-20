// https://codeforces.com/contest/276/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

class FenwickTree {
private:
    std::vector<long long> BIT1, BIT2;
    int n;
    void update(std::vector<long long>& BIT, int index, long long value) {
        while (index < n) {
            BIT[index] += value;
            index = index | (index + 1);
        }
    }
    long long query(const std::vector<long long>& BIT, int index) {
        long long sum = 0;
        while (index >= 0) {
            sum += BIT[index];
            index = (index & (index + 1)) - 1;
        }
        return sum;
    }
public:
    FenwickTree(int size) : n(size), BIT1(size, 0), BIT2(size, 0) {}
    void rangeUpdate(int left, int right, long long value) {
        update(BIT1, left, value);
        if (right + 1 < n)
            update(BIT1, right + 1, -value);
        update(BIT2, left, value * left);
        if (right + 1 < n)
            update(BIT2, right + 1, -value * (right + 1));
    }
    long long prefixSum(int index) {
        return query(BIT1, index) * (index + 1) - query(BIT2, index);
    }
    long long query(int left, int right) {
        if (left == 0)
            return prefixSum(right);
        else
            return prefixSum(right) - prefixSum(left - 1);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    vector<int> chains;
    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> depth(n + 1, 0);
    vector<int> chain_idx(n + 1, -1);

    function<void(int, int, int, int)> dfs = [&] (int u, int d, int p, int c) -> void {
        depth[u] = d;

        for (auto &v : adj[u]) {
            if (v == p) continue;

            c++;
            dfs(v, d + 1, u, c);
            c--;
        }

        if (u != 1 && adj[u].size() == 1) { 
            chains.push_back(c);
        }

        chain_idx[u] = chains.size() - 1;
    };

    int c = 0;
    dfs(1, 0, 0, c);

    vector<FenwickTree> Sts;

    int max_e = 0;
    for (int i=0; i<chains.size(); i++) {
        max_e = max(max_e, chains[i]);
        Sts.push_back(FenwickTree(chains[i]));
    }

    FenwickTree global_fenwick(max_e + 1);
    int rt_value = 0;

    int tp, v, x, d;
    while (q--) {
        cin >> tp;
        if (tp == 0) {
            cin >> v >> x >> d;
            int idx = chain_idx[v];

            if (v == 1) {
                rt_value += x;
                global_fenwick.rangeUpdate(0, d - 1, x);

                continue;
            }

            if (depth[v] - d >= 0) { 
                int lo = max(0LL, depth[v] - d - 1);
                int hi = min((int) chains[idx], depth[v] + d - 1);

                Sts[idx].rangeUpdate(lo, hi, x);

                if (depth[v] - d == 0) rt_value += x; 
            } else {
                rt_value += x;
                int rm = d - depth[v];
                int hi = rm - 1;

                global_fenwick.rangeUpdate(0, hi, x);

                if (hi < (depth[v] + d - 1)) {
                    Sts[idx].rangeUpdate(hi + 1, depth[v] + d - 1, x);
                }
            }
        } else if (tp == 1) {
            cin >> v;
            if (v == 1) cout << rt_value << "\n";
            else {
                int idx = chain_idx[v];
                int ans = Sts[idx].query(depth[v] - 1, depth[v] - 1);
                cout << ans + global_fenwick.query(depth[v] - 1, depth[v] - 1) << "\n";
            }
        }
    }

    return 0;
}