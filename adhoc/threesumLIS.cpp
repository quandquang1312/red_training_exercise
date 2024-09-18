// http://lgedvoj.lge.com/problem/threesumeasy

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

    int n; cin >> n;

    vector<int> arr(n), dp(n, 1), trace(n, -1);
    for (int i=0; i<n; i++) cin >> arr[i];

    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (arr[j] < arr[i]) {
                if (arr[j] + arr[i] > trace[i]) trace[i] = arr[j] + arr[i];
            }
        }
    }

    int ans = -1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (trace[j] == -1) continue;
            if (arr[j] < arr[i]) {
                ans = max(ans, trace[j] + arr[i]);
            }
        }
    }
    cout << ans << '\n';

    return 0;
}