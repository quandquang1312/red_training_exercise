// https://codeforces.com/problemset/problem/2070/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> p(n), depth(n, 0);
        vector<vector<int>> d_vct(n);

        d_vct[0].push_back(0);

        int max_depth = 0;

        for (int i=1, x; i<n; i++) {
            cin >> x; x--;
            p[i] = x;
            depth[i] = depth[x] + 1;
            max_depth = max(max_depth, depth[i]);
            d_vct[depth[i]].push_back(i);
        }

        vector<int> dp(n, 1);

        int below_sm = 0;
        for (int i=max_depth; i>=0; i--) {
            int cur_sm = 0;
            for (auto &u : d_vct[i]) {
                dp[u] = (dp[u] + below_sm) % MOD;
                cur_sm = (cur_sm + dp[u]) % MOD;
                if (p[u] != 0) dp[p[u]] = (dp[p[u]] - dp[u] + MOD) % MOD;
            }
            below_sm = cur_sm;
        }

        cout << dp[0] << "\n";
    }

    return 0;
}