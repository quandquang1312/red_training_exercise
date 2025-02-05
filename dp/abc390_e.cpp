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

    for (int i=0, v, x, c; i<n; i++) {
        cin >> v >> x >> c;
        arr[v].push_back({x, c}); 
    }

    // run dynamic programming to calculate the minimum calories to get X units of vitamin V
    vector<vector<int>> dp(3, vector<int>(x + 1, INF));

    for (int v=1; v<=3; v++) {
        int sz = arr[v].size();

        dp[v][0] = 0;

        for (int i=x; i>=1; i--) {
            for (int j=0; j<sz; j++) {
                
                if (dp[v][i] == INF) continue;
                int idx = i + arr[v][j].first;
                if (idx <= x) dp[v][idx] = min(dp[v][idx], dp[v][i] + arr[v][j].second); 
            }
        }
    }

    // run binary search to calculate the maximum minimum of all three vitamin

    return 0;
}