// https://codeforces.com/contest/474/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree {
private:
    int n;
    vector<pair<int, int>> tree;

    pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
        if (a.first > b.first) return a;
        else if (a.first == b.first) {
            if (a.second == -1) return b;
            return a;
        } else {
            return b;
        }
    }

    void update(int node, int tl, int tr, int pos, int val, int idx) {
        if (tl == tr) {
            tree[node] = {val, idx};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node * 2 + 1, tl, tm, pos, val, idx);
            else
                update(node * 2 + 2, tm + 1, tr, pos, val, idx);
            tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
        }
    }

    pair<int, int> query(int node, int tl, int tr, int l, int r) {
        if (l > r) return {0, -1};
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node * 2 + 1, tl, tm, l, min(r, tm)),
                     query(node * 2 + 2, tm + 1, tr, max(l, tm + 1), r));
    }

public:
    SegmentTree(int sz) : n(sz) {
        tree.assign(4 * n, {0, -1});
    }

    void update(int pos, int val, int idx) {
        update(0, 0, n - 1, pos, val, idx);
    }

    pair<int, int> query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, d; cin >> n >> d;

    vector<int> arr(n);
    vector<int> dp(n, 1), trace(n, -1);

    vector<int> points;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        points.push_back(arr[i] - d);
        points.push_back(arr[i] + d);
        points.push_back(arr[i]);
    }

    // Coordinate Compression
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(),points.end()), points.end());
    int sz = points.size();
    
    unordered_map<int, int> idx;
    for (int i=0; i<sz; i++) idx[points[i]] = i;

    int ans = 1, best_pos = 0;

    SegmentTree st(sz);
    st.update(idx[arr[0]], 1, 0);
    dp[0] = 1;

    for (int i=1; i<n; i++) {
        int lo = idx[arr[i] - d];
        int hi = idx[arr[i] + d];

        auto lo_p = st.query(0, lo);
        if ((lo_p.second != -1) && (1 + lo_p.first > dp[i])) {
            dp[i] = 1 + lo_p.first;
            trace[i] = lo_p.second;
        }

        auto hi_p = st.query(hi, sz - 1);
        if ((hi_p.second != -1) && (1 + hi_p.first > dp[i])) {
            dp[i] = 1 + hi_p.first;
            trace[i] = hi_p.second;
        } 

        st.update(idx[arr[i]], dp[i], i);
        if (ans < dp[i]) {
            ans = dp[i];
            best_pos = i;
        }
    }

    vector<int> rs;
    for (int i=best_pos; i!=-1; i=trace[i])
        rs.push_back(i + 1);
    reverse(rs.begin(), rs.end());

    cout << ans << "\n";
    for (auto &e : rs)
        cout << e << " ";

    return 0;
}