// https://codeforces.com/problemset/problem/189/A

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

    int n, arr[3];
    cin >> n >> arr[0] >> arr[1] >> arr[2];

    int dp[n+1];
    memset(dp, -1, sizeof dp);

    dp[0] = 0;
    for (int i=1; i<=n; i++) {
        for (int j=0; j<3; j++) {
            if (i - arr[j] >= 0) {
                dp[i] = max(dp[i], dp[i-arr[j]] + 1);
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}