// https://codeforces.com/contest/607/problem/B

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> arr;
vector<vector<int>> dp;

int solve(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];

    dp[l][r] = INF;

    dp[l][r] = min(dp[l][r], 1 + dp[l + 1][r]);
    if (arr[l] == arr[l+1]) dp[l][r] = min(dp[l][r], 1 + dp[l+2][r]);
    if (arr[l] == arr[r]) dp[l][r] = min(dp[l][r], dp[l+1][r-1]);

    for (int k=l+1; k<r; k++) {
        if (arr[l] == arr[k]) {
            if (l + 1 > k - 1) dp[l][r] = min(1 + solve(k + 1, r), dp[l][r]); 
            else dp[l][r] = min(solve(l + 1, k - 1) + solve(k + 1, r), \
                        dp[l][r]);
        }
    }

    return dp[l][r];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    arr.assign(n, 0);
    for (int i=0; i<n; i++) cin >> arr[i];

    dp.assign(n + 1, vector<int>(n + 1, -1));

    for (int i=0; i<n; i++) {
        dp[i][i] = 1;
        if (i + 1 >= n) continue;
        if (arr[i] == arr[i+1]) {
            dp[i][i+1] = 1; 
        } else {
            dp[i][i+1] = 2;
        }
    }

    for (int len=2; len<n; len++) {
        for (int i=0; i<(n-len); i++) {
            int j = i + len;
            if (arr[i] == arr[j] && dp[i+1][j-1] == 1) {
                dp[i][j] = 1;
            }
        }
    }

    for (int i=n-1; i>=0; i--) {
        for (int j=i+1; j<n; j++) {
            solve(i, j);
        }
    }

    cout << dp[0][n-1] << "\n";

    return 0;
}