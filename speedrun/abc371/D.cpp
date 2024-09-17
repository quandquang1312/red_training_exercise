#include <bits/stdc++.h>
using namespace std;

#define int long long
const int OFFSET = 1e9 + 10;

class FenwickTree {
public:
    FenwickTree(int n) {
        this->n = n;
        ft.assign(n + 5, 0);
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

    int n;
    cin >> n;

    vector<int> points;
    vector<pair<int, int>> coor(n);
    for (int i=0; i<n; i++) {
        cin >> coor[i].first;
        points.push_back(coor[i].first);
    }

    for (int i=0; i<n; i++) cin >> coor[i].second;

    int q; cin >> q;

    vector<pair<int, int>> queries;
    for (int i=0; i<q; i++) {
        int l, r; cin >> l >> r;
        queries.push_back({l, r});
        points.push_back(l);
        points.push_back(r);
    }

    // Coordinate Compression
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(),points.end()), points.end());
    int sz = points.size();

    unordered_map<int, int> idx;
    for (int i=1; i<=sz; i++) idx[points[i-1]] = i;

    FenwickTree ft(sz + 5);
    for (int i=0; i<n; i++) {
        ft.add(idx[coor[i].first], coor[i].second);
    }

    for (auto &[l, r] : queries) {
        int ans = ft.query(idx[l], idx[r]);
        cout << ans << '\n';
    }

    return 0;
}