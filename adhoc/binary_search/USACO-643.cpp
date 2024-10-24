#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #else
        freopen("diamond.in", "r", stdin);
        freopen("diamond.out", "w", stdout);
    #endif

    int n, k; cin >> n >> k;

    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    vector<int> maxx(n + 1), suffx(n + 1, 0), ed(n + 1, -1);
    for (int i=0; i<n; i++) {
        ed[i] = upper_bound(arr.begin(), arr.end(), arr[i] + k) - 1 - arr.begin();
        maxx[i] = ed[i] - i + 1;
    }

    for (int i=n-1; i>=0; i--) {
        suffx[i] = max(maxx[i], suffx[i+1]);
    }

    int ans = 0;
    for (int i=0; i<n; i++) {
        if (maxx[i] == 0) continue;
        ans = max(ans, maxx[i] + suffx[ed[i] + 1]);
    }

    cout << ans << "\n";

    return 0;
}