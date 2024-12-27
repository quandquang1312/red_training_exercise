// https://codeforces.com/contest/607/problem/A

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<pair<int, int>> arr(n);
    vector<int> arr_first(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i].first >> arr[i].second;
        arr[i].first = -arr[i].first;
        arr_first[i] = arr[i].first;
    }

    sort(arr.begin(), arr.end());
    sort(arr_first.begin(), arr_first.end());

    int ans = 0, nx = 0;
    vector<int> dp(n + 1, 0);

    for (int i=0; i<n; i++) {
        int cur_next =  upper_bound(arr_first.begin(), arr_first.end(), arr[i].first + arr[i].second) \
            - arr_first.begin();
        dp[i] = cur_next - i - 1;

        if (i < nx) continue;
        nx = cur_next;
        ans += (nx - i - 1);
    }

    for (int i=n-1; i>=0; i--) {
        int cur_next =  upper_bound(arr_first.begin(), arr_first.end(), arr[i].first + arr[i].second) \
            - arr_first.begin();

        dp[i] += dp[cur_next];
    }

    for (int i=0; i<n; i++) {
        ans = min(ans, i + 1 + dp[i + 1]);
    }

    cout << ans << "\n";

    return 0;
}