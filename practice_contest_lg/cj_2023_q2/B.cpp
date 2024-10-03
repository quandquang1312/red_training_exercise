// https://codejam.lge.com/problem/28312

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
        int n, m; cin >> n >> m;

        vector<int> arr(n), freq(n, 0);
        for (int i=0; i<n; i++) cin >> arr[i];

        int total = (n * (n + 1)) / 2;
        for (int i=0; i<n; i++) {
            if (i == 0 || i == n - 1) {
                freq[i] = total - (n * (n - 1)) / 2;
            } else {
                int lf = (i * (i + 1)) / 2;
                int rt = ((n - i) * ((n - i) + 1)) / 2;
                freq[i] = total - lf - rt - 1;
            }
        }

        vector<int> presum(n + 1, 0);
        for (int i=0; i<n; i++) {
            presum[i + 1] = presum[i] + freq[i] * arr[i];
            // cout << i << ": " << freq[i] << "\n";
        }

        int mmin = 1e9;
        for (int i=1; i<n-1; i++) {

            int k = i;
            int lf = presum[i];
            int rt = presum[n] - presum[i + 1];
            int mx = max(lf, rt);
            mmin = min(mmin, mx);
            cout << lf << " -" << i << "- " << rt << "\n";
        }

        cout << mmin << endl;

    }

    return 0;
}