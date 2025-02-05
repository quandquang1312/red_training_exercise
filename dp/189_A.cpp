// https://codeforces.com/problemset/problem/189/A

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<int> arr(3);

    cin >> arr[0] >> arr[1] >> arr[2];

    vector<int> dp(n + 1, -INF);
    dp[0] = 0;

    for (int i=1; i<=n; i++) {
        for (int j=0; j<3; j++) {
            if (i - arr[j] >= 0) dp[i] = max(dp[i], dp[i - arr[j]] + 1); 
        }
    }

    cout << dp[n] << "\n";

    return 0;
}