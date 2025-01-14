// https://codeforces.com/problemset/problem/296/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

void update(vector<int>& diff, int l, int r, int vl) {
    diff[l] += vl;
    diff[r + 1] -= vl;
}

void apply_update(vector<int>& diff)
{
    for (int i=1; i<diff.size(); i++) diff[i] += diff[i-1];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, k; cin >> n >> m >> k;

    vector<int> arr(n + 1, 0);
    vector<int> queries(m + 5, 0);

    for (int i=1; i<=n; i++) cin >> arr[i];

    vector<tuple<int, int, int>> ops;

    for (int i=0; i<m; i++) {
        int l, r, d; cin >> l >> r >> d;
        ops.push_back({l, r, d});
    }

    for (int i=0; i<k; i++) {
        int l, r; cin >> l >> r;
        update(queries, l, r, 1);
    }

    apply_update(queries);

    vector<int> diff(n + 5, 0);
    for (int i=0; i<ops.size(); i++) {
        int num = queries[i + 1];
        auto [l, r, d] = ops[i];
        if (num > 0)
            update(diff, l, r, d * num);
    }

    apply_update(diff);

    for (int i=1; i<=n; i++) {
        arr[i] += diff[i];
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}