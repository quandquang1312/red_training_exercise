// https://atcoder.jp/contests/abc389/tasks/abc389_f

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 5 * 1e5 + 5;

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

    int query(int r) {
        return sum(r);
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

    int n; cin >> n;

    FenwickTree ft(MAXN + 10);

    // dp[j] : the rating after n contests when initial is j
    // for (int i=0; i<n; i++)
    //     dp[j] = dp[j] + (dp[j] >= range[i].first && dp[j] <= range[i].second); 

    for (int i=0, a, b; i<n; i++) {
        cin >> a >> b;
        int lo = 1, hi = 1;

        // Find first initial rating j (smallest) where after i - 1 contest, its rating >= a
        int l = 1, r = MAXN;
        while (l < r) {
            int mid = (l + r) / 2;
            if (mid + ft.query(mid) >= a) { lo = mid; r = mid; }
            else { l = mid + 1; }
        }

        // Find first initial rating j (smallest) where after i - 1 contest, its rating > b
        l = 1, r = MAXN;
        while (l < r) {
            int mid = (l + r) / 2;
            if (mid + ft.query(mid) > b) { hi = mid; r = mid; }
            else { l = mid + 1; }
        }

        // update all the ratings (that after i - 1 contest, its rating in range a -> b
        // all this ratings would increase by 1
        ft.add(lo, 1);
        ft.add(hi, -1);
    }

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << x + ft.query(x) << "\n";
    }

    return 0;
}