// https://codejam.lge.com/problem/29891

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k; cin >> n >> k;

    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    int ans = 0LL;
    if (k == 1) {
        for (int i=0; i<n; i++)
            ans += abs(arr[i]) * 2;

        cout << ans << "\n";
    } else {
        sort(arr.begin(), arr.end());

        int ans = 0;
        for (int i=0; i<n && arr[i]<0; i+=k) {
            ans += abs(arr[i]) * 2;
        }

        for (int i=n-1; i>=0 && arr[i] > 0; i-=k) {
            ans += arr[i] * 2;
        }

        cout << ans << "\n";
    }

    return 0;
}