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

    int n; cin >> n;

    vector<int> arr(n);

    for (int i=0; i<n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    int ans = 0;
    int l = 0, r = n / 2;

    while (l < n / 2 && r < n) {
        if (arr[r] >= arr[l] * 2) {
            l++;
            r++;
            ans++;
        } else {
            r++;
        }
    }

    cout << ans << "\n";

    return 0;
}