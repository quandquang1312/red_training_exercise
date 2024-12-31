// https://codeforces.com/contest/1132/problem/F

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    string str; cin >> str;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i=0; i<n; i++) {
        dp[i][i] = 1;
    }

    for (int i=n-1; i>=0; i--) {
        for (int j=i; j<n; j++) {
            if (i == j) {
                dp[i][j] = 1;
                continue;
            }

            dp[i][j] = 1 + dp[i+1][j];

            for (int k=i+1; k<=j; k++) {
                if (str[i] == str[k])
                    dp[i][j] = min(dp[i][j], dp[i+1][k-1] + dp[k][j]);
            }
        }
    }

    cout << dp[0][n-1] << "\n";

    return 0;
}