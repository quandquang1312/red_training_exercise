// https://cses.fi/problemset/task/1074

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

    int n; cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    int median = arr[n/2];

    int ans = 0;
    for (int i=0; i<n; i++) {
        ans += abs(arr[i] - median);
    }

    cout << ans << "\n";

    return 0;
}