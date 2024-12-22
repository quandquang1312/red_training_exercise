// https://vjudge.net/problem/CSES-1090

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

    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    int ans = 0;
    int l = 0, cur = 0;
    for (int r=n-1; r>=l; r--) {
        ans++;
        if (r == l) break;
        if (arr[r] + arr[l] <= x) l++;
    }

    cout << ans << "\n";

    return 0;
}