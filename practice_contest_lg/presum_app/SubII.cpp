// https://cses.fi/problemset/task/1661

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

    int n, x; cin >> n >> x;
    vector<int> arr(n), presum(n + 1, 0);

    for (int i=0; i<n; i++) {
        cin >> arr[i];
        presum[i + 1] += presum[i] + arr[i];
    }

    map<int, int> mp;

    int ans = 0;
    for (int i=0; i<=n; i++) {
        if (mp.find(presum[i] - x) != mp.end())
            ans += mp[presum[i] - x];

        mp[presum[i]]++;
    }

    cout << ans << "\n";

    return 0;
}