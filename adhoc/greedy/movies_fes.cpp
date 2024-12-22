// https://cses.fi/problemset/task/1632

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

    int n, k; cin >> n >> k;

    vector<pair<int, int>> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i].first >> arr[i].second;

    sort(arr.begin(), arr.end(), [] (pair<int, int>& p1, pair<int, int>& p2) {
        return p1.second < p2.second;
    });

    multiset<int>  endpoints;
    for (int i=0; i<k; i++) endpoints.insert(0);

    int ans = 0;
    for (int i=0; i<n; i++) {
        auto it = endpoints.upper_bound(arr[i].first);
        if (it != endpoints.begin()) {
            it--;
            endpoints.erase(it);
            endpoints.insert(arr[i].second);
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}