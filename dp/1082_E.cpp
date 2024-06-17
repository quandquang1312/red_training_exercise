// https://codeforces.com/contest/1082/problem/E

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

    int n, c; cin >> n >> c;
    int arr[n], maxele = -1;

    for (int i=0; i<n; i++) {
        cin >> arr[i];
        maxele = max(maxele, arr[i]);
    }

    int dp[maxele+1] {};

    int cntC = 0, ans = 0, res = 0;
    for (int i=0; i<n; i++) {
        int d = arr[i];
        if (d == c) {
            cntC++; // + 1 is because arr[i] = c
            // ans + 1: max when stay changed from 0->i-1, + 1 is because arr[i] = c
            // cntC:  not change anything from 0->i-1 
            ans = max(ans + 1, cntC);
        } else {
            // dp[d]: changed all d from 0->i to c
            // dp[d] = max(dp[d], ans) keep dp[d] as maximum to change from 0->i
            ans = max(ans, 1 + dp[d]);
            dp[d] = max(dp[d] + 1, cntC + 1);
        }
    }

    res = max(res, ans);

    memset(dp, 0, sizeof dp);
    cntC = 0, ans = 0;
    for (int i=n-1; i>=0; i--) {
        int d = arr[i];
        if (d == c) {
            cntC++; // + 1 is because arr[i] = c
            // ans + 1: max when stay changed from 0->i-1, + 1 is because arr[i] = c
            // cntC:  not change anything from 0->i-1 
            ans = max(ans + 1, cntC);
        } else {
            // dp[d]: changed all d from 0->i to c
            // dp[d] = max(dp[d], ans) keep dp[d] as maximum to change from 0->i
            ans = max(ans, 1 + dp[d]);
            dp[d] = max(dp[d] + 1, cntC + 1);
        }
    }

    cout << max(res, ans) << endl;

    return 0;
}