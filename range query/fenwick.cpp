// https://open.kattis.com/problems/fenwick?tab=metadata

#include <bits/stdc++.h>
using namespace std;

const int MAXN = (5 * 1e3) + 5;
int n, q;

template <class T>
class FenwickTree {
private:
    vector<T> tree;
    int n;
public:
    FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }

    T query(int l, int r) { return query(r) - query(l - 1); }

    T query(int r) {
        T s = 0;
        while (r > 0) s += tree[r], r -= (r & (-r));
        return s;
    }

    void update(int i, T v) {
    while (i <= n) tree[i] += v, i += (i & (-i));
    }
};

int32_t main() {
    ios::sync_with_stdio(false);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n >> q;

    FenwickTree<int64_t> ft(n);

    int64_t a, b;
    for (int i=0; i<q; i++) {
        char ti; cin >> ti;
        if (ti == '+') {
            cin >> a >> b;
            ft.update(a + 1, b);
        } else {
            cin >> a;
            if (a == 0) cout << "0\n";
            else cout << ft.query(a) << "\n";
        }
    }
    return 0;
}