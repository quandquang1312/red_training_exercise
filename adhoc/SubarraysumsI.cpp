// https://cses.fi/problemset/task/1660

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, x, arr[200010] {};
    cin >> n >> x;

    for (int i=1; i<=n; i++) {
        cin >> arr[i];
    }

    int l = 0, sm = 0, ans = 0;
    for (int r=1; r<=n; r++) {
        sm += arr[r];
        while (l < r && sm - arr[l] >= x) {
            sm -= arr[l];
            l++;
        }

        if (sm == x) ans++;
    }

    cout << ans << endl;

    return 0;
}