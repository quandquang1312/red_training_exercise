// https://codeforces.com/problemset/problem/417/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 3e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m, b;
    cin >> n >> m >> b;

    vector<tuple<int, int, int>> arr(n);

    for (int i=0, x, k, p; i<n; i++) {
        cin >> x >> k >> p;
        int mask = 0;
        for (int j=0, d; j<p; j++) {
            cin >> d;
            mask |= (1 << (d - 1));
        }

        arr[i] = {k, x, mask}; 
    }

    sort(arr.begin(), arr.end());

    vector<int> dp((1 << m), INF);
    dp[0] = 0;

    int ans = INF;

    for (int i=0; i<n; i++) {
        auto [k, x, pmask] = arr[i];
        for (int mask=0; mask<(1 << m); mask++) {
            dp[mask | pmask] = min(dp[mask | pmask], dp[mask] + x);
            if ((mask | pmask) == ((1 << m) - 1)) {
                ans = min(ans, dp[mask | pmask] + k * b);
            }
        }
    }

    cout << (ans == INF ? -1 : ans) << "\n";

    return 0;
}