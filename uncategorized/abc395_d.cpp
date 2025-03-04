// https://atcoder.jp/contests/abc395/tasks/abc395_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;

    vector<int> current_nest(n + 1);
    vector<int> phy(n + 1), query(n + 1);

    for (int i=1; i<=n; i++) {
        current_nest[i] = i;
        phy[i] = i;
        query[i] = i;
    }

    int tp, a, b;
    while (q--) {
        cin >> tp;
        if (tp == 1) {
            cin >> a >> b;
            current_nest[a] = phy[b];
        } else if (tp == 2) {
            cin >> a >> b;

            swap(phy[a], phy[b]);
            swap(query[phy[a]], query[phy[b]]);
        } else {
            cin >> a;
            cout << query[current_nest[a]] << "\n";
        }
    }

    return 0;
}