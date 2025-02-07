// https://atcoder.jp/contests/abc390/tasks/abc390_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 3e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, x; cin >> n >> x;

    vector<vector<pair<int, int>>> arr(4);

    vector<int> mx_vit(4, 0);
    for (int i=0, v, x, c; i<n; i++) {
        cin >> v >> x >> c;
        arr[v].push_back({x, c});
        mx_vit[v] += x;
    }

    int mx = *min_element(mx_vit.begin() + 1, mx_vit.end());

    // dp[i][j]: the maximum vitamin i to get when we spend j calories
    vector<vector<int>> dp(4, vector<int>(x + 1, 0));

    for (int v=1; v<=3; v++) {
        int sz = arr[v].size();

        dp[v][0] = 0;

        for (int j=0; j<sz; j++) {
            int calories = arr[v][j].second;
            int vitamins = arr[v][j].first;

            for (int i=x; i>=calories; i--) {
                dp[v][i] = max(dp[v][i], dp[v][i - calories] + vitamins); 
            }
        }
    }

    auto min_calories = [&] (int b, const vector<int>& vit) -> int {
        int pos = lower_bound(vit.begin(), vit.end(), b) - vit.begin();
        return pos;
    };

    int lo = 0, hi = mx;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        int total = min_calories(mid, dp[1]) + min_calories(mid, dp[2]) + min_calories(mid, dp[3]);

        if (total <= x) lo = mid;
        else hi = mid - 1;
    }

    cout << lo << "\n";

    return 0;
}