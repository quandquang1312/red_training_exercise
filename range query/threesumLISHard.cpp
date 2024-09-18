// http://lgedvoj.lge.com/problem/threesumeasy

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return max(a, b);
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[node] = val;
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

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    SegmentTree st(MAXN + 5), st_2(MAXN + 5);
    vector<int> trace(n, -1);

    for (int i=0; i<n; i++) {
        int previous_max = st.query(1, arr[i] - 1);
        if (previous_max != 0) {
            trace[i] = previous_max + arr[i];
        }
        st.update(arr[i], arr[i]);
    }

    int ans = -1;
    for (int i=0; i<n; i++) {
        if (trace[i] == -1) continue;
        int previous_max_sum = st_2.query(1, arr[i] - 1);
        if (previous_max_sum != 0) {
            ans = max(ans, previous_max_sum + arr[i]);
        }

        st_2.update(arr[i], trace[i]);
    }

    cout << ans << '\n';

    return 0;
}