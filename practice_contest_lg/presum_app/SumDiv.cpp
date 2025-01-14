// https://cses.fi/problemset/task/1662

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("gen.txt", "r", stdin);
        freopen("solve.ans", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n), presum(n + 1, 0);

    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }

    for (int i=0; i<n; i++) {
        presum[i + 1] += (presum[i] + arr[i]) % n; 
    }

    map<int, int> mp;
    int ans = 0;
    for (int i=0; i<=n; i++) {
        if (mp.find(presum[i]) != mp.end())
            ans += mp[presum[i]];
        if (presum[i] < 0) {
            if (mp.find(n+presum[i]) != mp.end())
                ans += mp[n+presum[i]];
        } 
        if (presum[i] > 0) {
            if (mp.find(-(n-presum[i])) != mp.end())
                ans += mp[-(n-presum[i])];
        }

        mp[presum[i]]++; 
    }

    cout << ans << "\n";

    return 0;
}