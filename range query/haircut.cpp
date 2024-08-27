// https://usaco.org/index.php?page=viewproblem2&cpid=1041

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
        if (r < l) return 0;
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
        freopen("haircut.in", "r", stdin);
        freopen("haircut.out", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }

    FenwickTree ft(n + 5), ft_2(n + 5);

    for (int i=0; i<n; i++) {
        int ans_i = ft.query(arr[i] + 1, n + 4);
        ft.add(arr[i], 1);

        ft_2.add(arr[i], ans_i);
    }

    for (int i=0; i<n; i++) {
        cout << ft_2.query(0, i - 1) << "\n";
    }

    return 0;
}