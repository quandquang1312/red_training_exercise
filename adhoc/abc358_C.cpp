// https://atcoder.jp/contests/abc358/tasks/abc358_c

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    string s[n];
    for (int i=0; i<n; i++) {
        cin >> s[i];
    }

    int ans = 1e9;
    for (int i=0; i < (1 << n); i++) {
        bool filled[m] {0};
        for (int j=0; j<n; j++) {
            if (!(i & (1 << j))) continue;
            for (int k=0; k<m; k++) {
                if (s[j][k] == 'o') filled[k] = true;
            }
        }

        bool satisfied = true;
        for (int k=0; k<m; k++) {
            if (!filled[k]) satisfied = false;
        }

        if (satisfied) {
            if ((int) __builtin_popcount(i) < ans) {
                ans = min(ans, (int)__builtin_popcount(i));
                // cout << "i: " << i << endl;
            }
        }
    }

    cout << ans << endl;

    return 0;
}