// https://codeforces.com/contest/245/problem/H

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    string str; cin >> str;
    int n = str.size();
    
    // dp[i][j]: number of palindromes substring in range i-j
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<bool>> isPal(n, vector<bool>(n, false));

    for (int i=n-1; i>=0; i--) {
        dp[i][i] = 1;
        isPal[i][i] = true;
        for (int j=i+1; j<n; j++) {
            if (j == i + 1) {
                dp[i][j] = 2;
                isPal[i][j] = str[i] == str[j];
                dp[i][j] += isPal[i][j];
            } else {
                if (isPal[i+1][j-1] == true) isPal[i][j] = str[i] == str[j];
                dp[i][j] = isPal[i][j];
                dp[i][j] += dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        cout << dp[l-1][r-1] << '\n';
    }

    return 0;
}