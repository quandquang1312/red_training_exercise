#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

const int INF = 1e13;
const int MOD = 1e9 + 7;

#define LOG(...) print_with_dash(#__VA_ARGS__, __VA_ARGS__)

template<typename T>
void print_with_dash(const std::string& names, T value) {
    std::cout << names << ": " << value << std::endl;
}

template<typename T, typename... Args>
void print_with_dash(const std::string& names, T value, Args... args) {
    size_t pos = names.find(',');
    std::cout << names.substr(0, pos) << ": " << value << " - ";
    print_with_dash(names.substr(pos + 1), args...);
}

class SegmentTree { // 1-based index sum segment tree
private:
    int n, tree[MAXN*4], lazy[MAXN*4];
    vector<int> arr;

    void build(int node, int tl, int tr) {
        if (tl == tr) tree[node] = arr[tl];
        else {
            int tm = (tl + tr) >> 1;
            build(node*2, tl, tm);
            build(node*2+1, tm+1, tr);
            tree[node] = tree[node*2] + tree[node*2+1];
        }
    }

    int query(int node, int l, int r, int tl, int tr) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[node];
        push(node);
        int tm = (tl + tr) >> 1;
        return query(node*2, l, min(r, tm), tl, tm) + query(node*2+1, max(l, tm+1), r, tm+1, tr);
    }

    void push(int node) {
        if (lazy[node]) {
            tree[node*2] = tree[node*2+1] = tree[node];
            lazy[node*2] = lazy[node*2+1] = true;
            lazy[node] = false;
        }
    }

    void update(int node, int pos, int tl, int tr, int val) {
        if (tl == tr) tree[node] = val;
        else {
            int tm = (tl + tr) >> 1;

            if (pos <= tm) update(node*2, pos, tl, tm, val);
            else update(node*2+1, pos, tm+1, tr, val);

            tree[node] = tree[node*2] + tree[node*2+1];
        }
    }

    void rangeUpdate(int node, int l, int r, int tl, int tr, int val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            tree[node] = val;
            lazy[node] = true;
        } else {
            push(node);
            int tm = (tl + tr) >> 1;
            rangeUpdate(node*2, l, min(r, tm), tl, tm, val);
            rangeUpdate(node*2+1, max(l, tm+1), r, tm+1, tr, val);
        }
    }

public:
    SegmentTree(int sz) {
        n = sz;
        arr.resize(n+5, 0);
    }

    int query(int l, int r) {
        return query(1, l, r, 1, n);
    }

    void update(int pos, int val) {
        update(1, pos, 1, n, val);
    }

    void rangeUpdate(int l, int r, int val) {
        rangeUpdate(1, l, r, 1, n, val);
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
        int n, m; cin >> n >> m;
        // SegmentTree st(n);

        vector<int> arr(n);
        for (int i=1, d; i<=n; i++) {
            cin >> d;
            // st.update(i, d);
        }

        vector<int> t(m), L(m), R(m);

        for (int i=0; i<m; i++) cin >> t[i];
        for (int i=0; i<m; i++) cin >> L[i];
        for (int i=0; i<m; i++) cin >> R[i];

        LOG(m);
        return 0;

        int ori = 0, sign = 0;

        // for (int i=0; i<m; i++) {
        //     if (t[i] == 1) {
        //         ori = ori + L[i];
        //         if (ori >= n) ori = (ori - n) % n;
        //     } else if (t[i] == 2) {
        //         ori = ori - L[i];
        //         if (ori < 0) ori = (n + ori) % n;
        //     } else if (t[i] == 3) {
        //         sign = 1 - sign;
        //     } else if (t[i] == 4) {
        //         if (sign == 0) {
        //             if (ori + L[i] >= n) {
        //                 // st.rangeUpdate(ori, n-1, R[i]);
        //                 int rm = L[i] - ((n-1) - ori + 1); 
        //                 // st.rangeUpdate(0, rm, R[i]);
        //             } else {
        //                 st.rangeUpdate(ori, ori + L[i], R[i]);
        //             }
        //         } else {
        //             if (ori - L[i] >= 0) st.rangeUpdate(ori - L[i], ori, R[i]);
        //             else {
        //                 st.rangeUpdate(0, ori, R[i]);
        //                 int tt = (n - 1) - (L[i] - ori);
        //                 st.rangeUpdate(tt, n - 1, R[i]);
        //             }
        //         }
        //     } else {
        //         int ans = 0;
        //         if (sign == 0) {
        //             if (ori + L[i] >= n) {
        //                 ans = st.query(ori, n - 1);
        //                 ans += st.query(0, L[i] - (n - ori) - 1);
        //             } else {
        //                 ans = st.query(ori, ori + L[i] - 1);
        //             }
        //         } else {
        //             if (L[i] <= ori) {
        //                 ans += st.query(ori - L[i], ori);
        //             } else {
        //                 ans += st.query(0, L[i]);
        //             }
        //         }
        //         cout << ans << " ";
        //     }
        // }

        cout << "\n";

    }

    return 0;
}