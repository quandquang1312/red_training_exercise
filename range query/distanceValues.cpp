// https://cses.fi/problemset/task/1734

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
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }

    vector<vector<pair<int, int>>> query(n);
    for (int i=0; i<q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        query[a].push_back({b, i});
    }

    FenwickTree ft(n);
    unordered_map<int, int> lst_idx;
    vector<int> sol(q);
    for (int i=n-1; i>=0; i--) {
        int val = arr[i];

        if (lst_idx.count(val) > 0) ft.add(lst_idx[val], -1);
        lst_idx[val] = i;
        ft.add(i, 1);

        for (auto &e : query[i]) {
            sol[e.second] = ft.query(i, e.first);
        }
    }

    for (auto &e : sol) cout << e << "\n";

    return 0;
}