// https://codejam.lge.com/problem/27898

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
        int n, m, q; cin >> n >> m >> q;
        vector<pair<int, int>> points(n), sheets(m);

        for (int i=0; i<n; i++) cin >> points[i].first >> points[i].second;
        for (int i=0; i<m; i++) cin >> sheets[i].first >> sheets[i].second;

        auto isInside = [](pair<int, int> p, pair<int, int> s) {
            return (p.first <= s.first && p.second <= s.second);
        };

        FenwickTree ft(m+1);

        for (int i=0; i<n; i++) {
            int cnt = 0;
            for (int j=0; j<m; j++) {
                if (isInside(points[i], sheets[j])) cnt++;
            }
            ft.add(cnt, 1);
        }

        while (q--) {
            int li, ui; cin >> li >> ui;
            int ans = ft.query(li, ui);
            cout << ans << " ";
        }
        cout << endl;
    }

    return 0;
}