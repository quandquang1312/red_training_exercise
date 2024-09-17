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

    int tc; cin >> tc;
    while (tc--) {
        int n, m, q; cin >> n >> m >> q;

        vector<int> arr(m);
        for (int i=0; i<m; i++) cin >> arr[i];
        sort(arr.begin(), arr.end());

        int x; cin >> x;

        if (arr[0] > x) {
            cout << arr[0] - 1 << "\n";
        } else if (arr[m - 1] < x) {
            cout << n - arr[m -1] << "\n";
        } else {
            int upp = upper_bound(arr.begin(), arr.end(), x) - arr.begin();
            int low = lower_bound(arr.begin(), arr.end(), x) - arr.begin() - 1;
            cout << (arr[upp] - arr[low]) / 2 << '\n';
        }
    }

    return 0;
}