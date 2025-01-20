// https://atcoder.jp/contests/abc374/tasks/abc374_c

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n);

    vector<int> prefix_sum(n + 1, 0);
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        prefix_sum[i + 1] = prefix_sum[i] + arr[i];
    }

    int ans = INF;
    for (int i=0; i < (1 << n); i++) {
        int sm = 0, sm2 = 0;
        for (int j=0; j<n; j++) {
            if (i & (1 << j)) {
                sm += arr[j];
            }
        }

        ans = min(ans, max(sm, prefix_sum[n] - sm));
    }

    cout << ans << endl;

    return 0;
}