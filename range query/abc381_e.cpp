// https://atcoder.jp/contests/abc381/tasks/abc381_e

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, q; cin >> n >> q;

    string str; cin >> str;

    vector<int> prefix_1(n + 1, 0);
    vector<int> prefix_2(n + 1, 0);
    vector<int> slash_pos;

    for (int i=0; i<n; i++) {
        int add_1 = str[i] == '1';
        int add_2 = str[i] == '2';
        if (str[i] == '/') slash_pos.push_back(i + 1);
        prefix_1[i + 1] += add_1 + prefix_1[i];
        prefix_2[i + 1] += add_2 + prefix_2[i];
    }

    while (q--) {
        int l, r; cin >> l >> r;
        if (slash_pos.empty()) {
            cout << "0\n";
            continue;
        }

        int lo = lower_bound(slash_pos.begin(), slash_pos.end(), l) - slash_pos.begin();
        int hi = lower_bound(slash_pos.begin(), slash_pos.end(), r) - slash_pos.begin();
        if (lo == slash_pos.size()) lo -= 1;
        if (hi == slash_pos.size()) hi -= 1;

        int ans = 0;
        hi = (slash_pos[hi] > r ? hi - 1 : hi);
        for (int i=lo; i<slash_pos.size() && i<=hi; i++) {
            if (slash_pos[i] >= l && slash_pos[i] <= r) {
                int n1s = prefix_1[slash_pos[i]] - prefix_1[l - 1];
                int n2s = prefix_2[r] - prefix_2[slash_pos[i] - 1];
                ans = max(ans, min(n1s, n2s) * 2 + 1);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}