// https://usaco.org/index.php?page=viewproblem2&cpid=693

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
    #else
        freopen("bphoto.in", "r", stdin);
        freopen("bphoto.out", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n), points;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        points.push_back(arr[i]);
    }

    sort(points.begin(), points.end());
    points.erase(unique(points.begin(),points.end()), points.end());
    int sz = points.size();

    unordered_map<int, int> idx;
    for (int i=0; i<sz; i++) idx[points[i]] = i;

    FenwickTree ft_1(sz + 5), ft_2(sz + 5);

    vector<int> L(n), R(n);
    for (int i=0; i<n; i++) {
        int val = idx[arr[i]];
        L[i] = ft_1.query(val + 1, sz);
        ft_1.add(val, 1);
    }

    for (int i=n-1; i>=0; i--) {
        int val = idx[arr[i]];
        R[i] = ft_2.query(val + 1, sz);
        ft_2.add(val, 1);
    }

    int ans = 0;
    for (int i=0; i<n; i++) {
        // cout << i << ": " << L[i] << "-" << R[i] << '\n';
        if (min(R[i], L[i]) * 2 < max(R[i], L[i])) ans++;
    }

    cout << ans << endl;

    return 0;
}