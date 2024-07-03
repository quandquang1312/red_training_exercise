// https://open.kattis.com/problems/neighborhoodwatch

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

    int n, k; cin >> n >> k;

    FenwickTree ft(n+1);
    for (int i=0; i<k; i++) {
        int x; cin >> x;
        ft.add(x, 1);
    }

    int ans = 0;
    for (int i=1; i<=n; i++) {
        if (ft.query(i, i) == 1) {
            ans += n - i + 1;
        } else {
            int l = i, r = n;
            while (l < r) {
                int m = (l + r) >> 1;
                if (ft.query(i, m) >= 1) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }

            if (ft.query(i, l) >= 1) ans += n - l + 1;
        }
    }

    cout << ans << endl;

    return 0;
}