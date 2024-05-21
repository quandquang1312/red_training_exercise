// https://atcoder.jp/contests/abc353/tasks/abc353_c

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e8;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<int> arr(n+1), presum(n+1, 0);

    for (int i=1; i<=n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    for (int i=1; i<=n; i++) presum[i] = presum[i-1] + arr[i];

    int ans = 0;
    for (int i=1; i<=n; i++) {
        if (i == n) break;

        int rm   = MOD - arr[i];
        int rm_n = n - i;
 
        int pos = lower_bound(arr.begin() + i + 1, arr.end(), rm) - (arr.begin() + i + 1);

        if (arr[pos] + arr[i] >= MOD)  pos--;

        int lesser_cnt  = pos;
        int greater_cnt = rm_n - pos;

        int lesser_sum = 0, greater_sum = 0;
        int st = i, mid = i + lesser_cnt , en = n;
        if (lesser_cnt > 0)  lesser_sum = lesser_cnt * arr[i] + (presum[mid] - presum[st]);
        if (greater_cnt > 0) greater_sum = greater_cnt * arr[i] + (presum[en] - presum[mid]) - greater_cnt * MOD;

        ans += lesser_sum + greater_sum;
    }

    cout << ans << endl;

    return 0;
}