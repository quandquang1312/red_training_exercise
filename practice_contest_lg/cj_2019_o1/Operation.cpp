// https://codejam.lge.com/problem/17126

#include <bits/stdc++.h>
using namespace std;

#define int long long

class FenwickTree {
public:
    FenwickTree(int n) {
        this->n = n;
        ft.assign(n, 0);
    }

    FenwickTree(vector<int> arr) : FenwickTree(arr.size()) {
        for (int i=0; i<arr.size(); i++)
            add(i, arr[i]);
    }

    int query(int l, int r) {
        return sum(r) - sum(l-1);
    }

    void add(int idx, int vl) {
        for (; idx < n; idx = idx | (idx + 1))
            ft[idx] += vl;
    }

private:
    vector<int> ft;
    int n;

private:
    int g(int i) { return i & (i + 1); }
    int sum(int i) {
        int rs = 0;
        while (i >= 0) {
            rs += ft[i];
            i = g(i) - 1;
        }
        return rs;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<tuple<int, string, string>> ops;
    vector<string> points;

    for (int i=0; i<n; i++) {
        int tp; cin >> tp;
        if (tp == 1) {
            string k, v; cin >> k >> v;
            ops.push_back({tp, k, v});
            points.push_back(k);
        } else if (tp == 2) {
            string l, r; cin >> l >> r;
            ops.push_back({tp, l, r});
            points.push_back(l);
            points.push_back(r);
        } else {
            string pos; cin >> pos;
            ops.push_back({tp, pos, "-"});
            points.push_back(pos);
        }
    }

    // Coordinate Compression
    sort(points.begin(), points.end(), [](string a, string b) {
        if (a.size() == b.size()) return a < b;
        return a.size() < b.size();
    });
    points.erase(unique(points.begin(),points.end()), points.end());
    int sz = points.size();

    unordered_map<string, int> idx;
    for (int i=1; i<=sz; i++) idx[points[i-1]] = i;

    FenwickTree ft(sz + 5);
    for (auto &[tp, a, b] : ops) {
        if (tp == 1) {
            int pos = idx[a];
            int val = stoi(b);
            ft.add(pos, val);
            int sm = ft.query(1, sz);
            cout << sm << " ";
        } else if (tp == 2) {
            int l = idx[a], r = idx[b];
            int sm = ft.query(l, r);
            cout << sm << " ";
        } else if (tp == 3) {
            int pos = idx[a];
            int old_val = ft.query(pos, pos);
            ft.add(pos, -old_val);
            int sm = ft.query(1, sz);
            cout << sm << " ";
        }
    }

    cout << "\n";

    return 0;
}