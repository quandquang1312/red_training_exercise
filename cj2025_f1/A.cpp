
#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<int> arr(n), c(m), presum(n + 1);
    for (int i=0; i<n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    for (int i=0; i<m; i++) {
        cin >> c[i];
        c[i] -= i;
    }

    for (int i=0; i<n; i++) {
        presum[i + 1] = presum[i];
        presum[i + 1] += arr[i];
    }

    int total = 0;

    for (int i=0; i<m; i++) {
        auto it = upper_bound(arr.begin(), arr.end(), c[i]);
        if (it != arr.end()) {
            int j = it - arr.begin();
            int sm = presum[n] - presum[j];

            int cur = sm - (c[i] * (n - j)) - total;

            if (cur < 0) cur = 0;

            cout << cur << "\n";
            total += cur;
        } else {
            cout << 0 << "\n";
        }
    }

    return 0;
}