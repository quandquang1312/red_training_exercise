// https://cses.fi/problemset/task/1748

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return ((a % MOD) + (b % MOD)) % MOD;
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[node] += val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node*2, tl, tm, pos, val);
            else
                update(node*2+1, tm+1, tr, pos, val);
            tree[node] = merge(tree[node*2], tree[node*2+1]);
        }
    }

    int query(int node, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node*2, tl, tm, l, min(r, tm)),
               query(node*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(int sz) : n(sz + 5) {
        tree.assign(4 * n, 0);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n), points;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        points.push_back(arr[i]);
    }

    // Coordinate Compression
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(),points.end()), points.end());
    int sz = points.size();

    unordered_map<int, int> idx;
    for (int i=1; i<=sz; i++) idx[points[i-1]] = i;

    SegmentTree st(sz);
    int ans = 0;
    for (int i=0; i<n; i++) {
        int vl = idx[arr[i]];
        int ans_i = st.query(1, vl - 1) + 1;
        ans = (ans + ans_i) % MOD;
        st.update(vl, ans_i);
    }

    cout << ans << endl;

    return 0;
}