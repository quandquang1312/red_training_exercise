// https://codeforces.com/contest/2057/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

class SegmentTree {
public:
    int n;
    vector<int> tree_min, tree_max, ans;

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree_min[node] = tree_max[node] = val;
        } else {
            int tm = (tl + tr) >> 1;

            if (pos <= tm) update(node * 2, tl, tm, pos, val);
            else update(node * 2 + 1, tm + 1, tr, pos, val);

            ans[node] = max(ans[node * 2], ans[node * 2 + 1]);
            ans[node] = max(ans[node], tree_max[node * 2 + 1] - tree_min[node * 2]);

            tree_min[node] = min(tree_min[node * 2], tree_min[node * 2 + 1]);
            tree_max[node] = max(tree_max[node * 2], tree_max[node * 2 + 1]);
        }
    }

public:
    SegmentTree(int sz) : n(sz) {
        tree_min.assign(4 * n, INF);
        tree_max.assign(4 * n, -INF);
        ans.assign(4 * n, 0);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, q; cin >> n >> q;

        vector<int> arr(n + 1);

        SegmentTree st_1(n + 1);
        SegmentTree st_2(n + 1);
        for (int i=1; i<=n; i++) {
            cin >> arr[i];
            st_1.update(i, arr[i] - i);
            st_2.update(i, -arr[i] - i);
        }

        for (int i=0; i<=q; i++) {
            if (i) {
                int pos, val; cin >> pos >> val;
                st_1.update(pos, val - pos);
                st_2.update(pos, -val - pos);
            }

            int ans = max(st_1.ans[1], st_2.ans[1]);
            cout << ans << "\n";
        }
    }

    return 0;
}