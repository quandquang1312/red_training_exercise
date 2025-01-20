// https://codeforces.com/contest/2019/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return min(a, b);
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

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> cities(n + 1);
        SegmentTree st(n + 1);

        for (int i=1; i<=n; i++) {
            cin >> cities[i];
            st.update(i, cities[i]);
        }

        int ans = 0;
        for (int i=1; i<=n; i++) {
            if (i == 1) {
                int mmin = st.query(i + 1, n);
                if (mmin >= n) ans++;
            } else if (i == n) {
                int mmin = st.query(1, n - 1);
                if (mmin >= n) ans++;
            } else {
                bool poss = false;

                int l_min = st.query(1, i - 1);
                int r_min = st.query(i + 1, n);

                // left move
                if ((l_min >= i) && (r_min >= (i * 2 + (n - i)))) poss = true;

                // right move
                if ((l_min >= (n - 1) * 2 + (i - 1)) && (r_min <= (n - i))) poss = true;

                if (poss) ans++;
            }
        }
        
        cout << ans << endl;
    }

    return 0;
}