// https://codeforces.com/gym/102694/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> startIdx, endIdx, parent;;
vector<int> val;
int timer = 1;

void euler_tour(int at, int prev) {
    startIdx[at] = timer++;
    for (int n : adj[at]) {
        if (n != prev) { 
            parent[n] = at;
            euler_tour(n, at);
        }
    }
    endIdx[at] = timer;
}

class SegmentTree {
private:
    int n;
    vector<double> tree;

    double merge(double a, double b) {
        return a * b;
    }

    void update(int node, int tl, int tr, int pos, double val) {
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

    double query(int node, int tl, int tr, int l, int r) {
        if (l > r) return 1.0;
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node*2, tl, tm, l, min(r, tm)),
               query(node*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(int sz) : n(sz) {
        // Assign 1
        tree.assign(4 * n + 5, 1.0);
    }

    void update(int pos, double val) {
        update(1, 1, n, pos, val);
    }

    double query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};


int brute(int u, int prev) {
    int ans = val[u];
    for (auto &v : adj[u]) {
        if (v == prev) continue;
        ans = ans * brute(v, u);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    startIdx.assign(n * 2, 0);
    endIdx.assign(n * 2, 0);
    val.assign(n, 1);
    parent.assign(n, 0);
    adj.resize(n);

    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    euler_tour(0, 0);

    // for (int i=0; i<n; i++) {
    //     cout << i << ": " << parent[i] << " - " << endIdx[i] << "\n"; 
    // }

    SegmentTree st(timer + 5);
    auto prt = [&]() {
        for (int i=1; i<timer; i++) {
            cout << st.query(i,i) << " ";
        }
        cout << "\n";
    };

    int q; cin >> q;
    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            x--;
            st.update(startIdx[x], y);
            // double update_y = (double) (1.0 / y);
            // st.update(endIdx[x], update_y);
            // if (x) st.update(endIdx[parent[x]], y);
            // // cout << "update: " << x << " - " << y << "\n";
            // val[x] = y;
        } else { // t == 2
            x--, y--;
            // int product_x_brute = brute(x, parent[x]);
            // int product_y_brute = brute(y, parent[y]);
            double product_x = st.query(startIdx[x], endIdx[x] - 1);
            double product_y = st.query(startIdx[y], endIdx[y] - 1);
            // cout << product_x << " - " << product_y << "\n";
            double ans = (1.0 * product_x) / (1.0 * product_y);
            // double ans_brute = (1.0 * product_x_brute) / (1.0 * product_y_brute);
            // cout << ans << " <-> " << " " << "\n";
            if (ans > 1000000000) cout << "1000000000\n";
            else cout << ans << "\n";
        }
        // prt();
    }

    return 0;
}