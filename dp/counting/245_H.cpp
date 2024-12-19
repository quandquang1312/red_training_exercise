// https://codeforces.com/contest/245/problem/H

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    string str; cin >> str;
    str = ' ' + str;
    int n = str.size() + 1;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i=1; i<=n; i++) dp[i][i] = 1;
    for (int i=1; i<=n-1; i++) {
        if (str[i] == str[i+1]) dp[i][i+1] = 1;
    }

    for (int len=2; len<=n; len++) {
        for (int i=1; i + len <= n; i++) {
            int j = i + len;
            if (str[i] == str[j] && dp[i+1][j-1] == 1) {
                dp[i][j] = 1;
            }
        }
    }

    vector<vector<int>> cnt(n + 1, vector<int>(n + 1, 0));
    for (int i=n; i>=1; i--) {
        for (int j=i; j<n; j++) {
            cnt[i][j] = cnt[i+1][j] + cnt[i][j-1] - cnt[i+1][j-1] + dp[i][j];
        }
    }

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;

        cout << cnt[l][r] << "\n";
    }

    return 0;
}