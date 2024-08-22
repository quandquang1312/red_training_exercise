// https://open.kattis.com/problems/muzicari

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

    int t, n;
    cin >> t >> n;

    vector<int> arr(n);

    for (int i=0; i<n; i++) cin >> arr[i];

    vector<vector<int>> dp(n + 1, vector<int>(t * 2 + 10, 0));

    for (int i=1; i<=n; i++) {
        int val = arr[i - 1];
        for (int j=0; j<=t*2 + 1; j++) {
            dp[i][j] = dp[i-1][j];
            if (j - val >= 0) {
                if (dp[i-1][j-val] + val > dp[i][j]) {
                    dp[i][j] = dp[i-1][j-val] + val;
                }
            }
        }
    }

    // trace snapsack solution
    int res = dp[n][t], sm = t;
    vector<int> trace;
    for (int i=n; i >= 0 && res > 0; i--) {
        if (res != dp[i-1][sm]) {
            trace.push_back(i - 1);
            res -= arr[i - 1];
            sm  -= arr[i - 1];
        }
    }

    int ans[n] {}, lst = 1;
    for (int i=0; i<trace.size(); i++) {
        int idx = trace[i];
        ans[idx] = lst;
        lst += arr[idx];
    }

    lst = 1;
    for (int i=0; i<n; i++) {
        if (ans[i] == 0) {
            ans[i] = lst;
            lst += arr[i];
        }
    }

    for (int i=0; i<n; i++) {
        cout << ans[i] - 1 << ' ';
    }

    cout << '\n';

    return 0;
}