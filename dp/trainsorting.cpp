// https://open.kattis.com/problems/trainsorting

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    int arr[n];

    for (int i=0; i<n; i++) cin >> arr[i];

    vector<int> LIS(n, 1), LDS(n, 1);

    int ans = 0;
    for (int i=n-1; i>=0; i--) {
        for (int j=n-1; j>i; j--) {
            if (arr[j] > arr[i]) LIS[i] = max(LIS[i], LIS[j] + 1);
            if (arr[j] < arr[i]) LDS[i] = max(LDS[i], LDS[j] + 1);
        }
        ans = max(ans, LIS[i] + LDS[i] - 1);
    }

    cout << ans << '\n';
    return 0;
}