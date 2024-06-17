// https://codeforces.com/contest/687/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 510

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, k, arr[MAXN];
    bool dp[MAXN][MAXN];
    cin >> n >> k;

    memset(dp, false, sizeof dp);
    dp[0][0] = 1;

    for (int i=0; i<n; i++) cin >> arr[i];

    for (int i=0; i<n; i++) {
        for (int j=k; j>=0; j--) {
            for (int z=j; z>=0; z--) {
                if (j - arr[i] >= 0) {
                    dp[j][z] |= dp[j-arr[i]][z];
                    if (z - arr[i] >= 0) dp[j][z] |= dp[j-arr[i]][z-arr[i]]; 
                }
            }
        }
    }

    vector<int> ans;
    for (int i=0; i<=k; i++) {
        if (dp[k][i]) ans.push_back(i);
    }

    cout << ans.size() << endl;
    for (auto &e : ans) {
        cout << e << " ";
    }
    cout << endl;

    return 0;
}