// https://codeforces.com/problemset/problem/1526/C2

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF -1e18

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }

    vector<vector<pair<int, int>>> dp(n + 1, vector<pair<int, int>>(2, {0, 0}));

    // not choose
    dp[0][0] = {0, 0};

    // choose
    if (arr[0] >= 0) {
        dp[0][1] = {arr[0], 1};
    }

    for (int i=1; i<n; i++) {

    } 


    return 0;
}