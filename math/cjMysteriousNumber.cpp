// https://codejam.lge.com/problem/17433

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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];

        sort(arr.begin(), arr.end());

        if (arr[0] == arr[n - 1]) {
            cout << "INFINITY\n";
            continue;
        }

        vector<int> diff(n - 1);
        for (int i=0; i<n-1; i++) {
            diff[i] = (arr[i + 1] - arr[i]);
        }

        int ans = diff[0];
        for (int i=1; i<diff.size(); i++) {
            ans = __gcd(ans, diff[i]);
        }

        cout << ans << '\n';
    }

    return 0;
}