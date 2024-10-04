// https://codejam.lge.com/problem/27362

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
        int n, k; cin >> n >> k;

        vector<int> A(n), B(n);
        for (int i=0; i<n; i++) cin >> A[i];
        for (int i=0; i<n; i++) cin >> B[i];

        vector<int> AmB(n), ApB(n);
        for (int i=0; i<n; i++) {
            AmB[i] = A[i] - B[i];
            ApB[i] = A[i] + B[i];
        }

        sort(AmB.begin(), AmB.end());
        sort(ApB.begin(), ApB.end());

        for (int i=0; i<n; i++) {
            int val = AB[i];
            if (val < 0 && abs(val) > k) {
                // find abs(val) - k
                int pos = lower_bound(AB.begin() + i + 1, AB.end(), (abs(val) - k)) - AB.begin();
            } else {
                // find k - val
                int pos = lower_bound();
            }
        }

        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                int xij = A[i] - A[j], yij = B[i] - B[j];
                int zij = abs(xij - yij);
                printf("[%d][%d]: - X: %d, Y: %d, Z: %d\n", i, j, xij, yij, zij);
            }
        }

        // X[i][j] = A[i] - A[j], i < j
        // Y[i][j] = B[i] - B[j], i < j
        // Z[i][j] = |X[i][j] - Y[i][j]|

        // Z[i][j] always equal or greater than 0
        // 

    }

    return 0;
}