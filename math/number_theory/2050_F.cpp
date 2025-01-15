#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> buildSparseTable(const vector<int>& arr) {
    int n = arr.size();
    int maxLog = 32 - __builtin_clz(n); 
    vector<vector<int>> st(n, vector<int>(maxLog));

    for (int i = 0; i < n; i++) st[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    return st;
}

int queryGCD(const vector<vector<int>>& st, int l, int r) {
    int range = r - l + 1;
    int log = 31 - __builtin_clz(range); 
    return gcd(st[l][log], st[r - (1 << log) + 1][log]);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, q; cin >> n >> q;
        vector<int> arr(n), diff(n - 1);

        for (int i = 0; i < n; i++) cin >> arr[i];
        for (int i = 0; i < n - 1; i++) {
            diff[i] = abs(arr[i + 1] - arr[i]);
        }

        auto st = buildSparseTable(diff);

        for (int i = 0, l, r; i < q; i++) {
            cin >> l >> r;
            l--, r--;
            if (l == r) cout << 0 << " ";
            else cout << queryGCD(st, l, r - 1) << " ";
        }

        cout << "\n";
    }

    return 0;
}
