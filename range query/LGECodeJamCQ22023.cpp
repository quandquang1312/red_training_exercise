// https://codejam.lge.com/problem/27898

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 100010;

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return a + b;
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
    SegmentTree(int sz) : n(sz) {
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

    int tc; cin >> tc;
    while (tc--) {
        int n, m, q; cin >> n >> m >> q;

        vector<tuple<int, int, int>> points(n + m);

        for (int i=0, x, y; i<n + m; i++) {
            cin >> x >> y;
            points[i] = {x, y, (i < n)};
        }

        sort(points.begin(), points.end(), [] (const tuple<int, int, int> &p1, const tuple<int, int, int> &p2) {
            auto &[x1, y1, t1] = p1;
            auto &[x2, y2, t2] = p2;

            if (x1 == x2) {
                if (y1 == y2) return t1 < t2;
                return y1 > y2;
            }
            return x1 > x2;
        });

        SegmentTree st(MAXN);

        vector<int> ans(MAXN, 0); 

        for (int i=0; i<n + m; i++) {
            auto &[x, y, t] = points[i];
            if (t == 1) { // point
                int c = st.query(y, MAXN - 1);
                ans[c + 1]++;
            } else { // sheet
                st.update(y, 1);
            }
        }

        for (int i=1; i<MAXN; i++) ans[i] += ans[i - 1];

        int l, r;
        while (q--) {
            cin >> l >> r;
            l++, r++;

            cout << ans[r] - ans[l - 1] << " ";
        }

        cout << "\n";
    }

    return 0;
}