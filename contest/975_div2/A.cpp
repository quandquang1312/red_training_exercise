// https://codeforces.com/contest/2019/problem/0

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
        int n; cin >> n;
        vector<int> arr(n);

        for (auto &e : arr) cin >> e;

        // odd take
        int sm_odd = 0, max_odd = 0;
        int sm_eve = 0, max_eve = 0;
        for (int i=0; i<n; i++) {
            if (i % 2 == 0) {
                sm_eve++;
                max_eve = max(max_eve, arr[i]);
            } else {
                sm_odd++;
                max_odd = max(max_odd, arr[i]);
            }
        }

        cout << max(sm_odd + max_odd, sm_eve + max_eve) << "\n";
    }

    return 0;
}