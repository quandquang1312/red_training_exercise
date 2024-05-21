// https://vjudge.net/problem/UVA-11420

#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, s, dp[70][2][70];

int solve(int idx, bool aboveLocked, int nos) {
    if (nos < 0) return 0;
    if (idx == 0) return nos == 0;

    int &ans = dp[idx][aboveLocked][nos];
    if (ans != -1) return ans;

    if (aboveLocked) {
        ans = solve(idx + 1, true, nos - 1) + solve(idx + 1, false, nos);
    } else {
        ans = solve(idx + 1, true, nos) + solve(idx + 1, false, nos);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, -1, sizeof(dp));
    while (scanf("%lld %lld", &n, &s) != EOF) {
        if (n < 0) break;
        int ans = solve(n, true, s);
        cout << ans << endl;
    }

    return 0;
}