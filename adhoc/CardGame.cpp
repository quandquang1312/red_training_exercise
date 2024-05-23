// http://lgedvoj.lge.com/problem/cardgame

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e18

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, k;
    cin >> n >> k;

    int arr[n+1];
    vector<int> presum(n+1, 0), sufsum(n+2, 0);
    for (int i=1; i<=n; i++) {
        cin >> arr[i];
        presum[i] += presum[i-1] + arr[i];
    }

    for (int i=n; i>=1; i--) sufsum[i] += sufsum[i+1] + arr[i];


    int ans = INF;
    for (int i=n; i>=1; i--) {
        int pos = lower_bound(presum.begin(), presum.end(), k - sufsum[i]) - presum.begin();
        if (pos >= 0 && pos <= n) {
            if ((presum[pos] + sufsum[i] == k) && (pos < i)) {
                ans = min(ans, pos + (n - i + 1));
            }
        }
    }

    ans = ans == INF ? -1 : ans;
    cout << ans << endl;

    return 0;
}