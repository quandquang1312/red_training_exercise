// https://open.kattis.com/problems/moviecollection

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

    int tc; cin >> tc;
    while (tc--) {
        int n, q; cin >> n >> q;

        FenwickTree ft(n + q + 10);
        vector<int> idx(n + 1, 0);

        for (int i=1; i<=n; i++) {
            ft.add(i, 1);
            idx[i] = n - i + 1;
        }

        int it = n + 1;
        while (q--) {
            int x; cin >> x;

            int pos = idx[x];
            int sm  = n - ft.query(0, pos);
            
            cout << sm << " ";

            ft.add(pos, -1);
            idx[x] = it;
            ft.add(idx[x], 1);

            it++;
        }

        cout << "\n";
    }

    return 0;
}