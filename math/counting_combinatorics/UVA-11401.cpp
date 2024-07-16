// https://vjudge.net/problem/UVA-11401

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 1000000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int dp[MAXN] {}, ans[MAXN] {};
    int prev_max = 1, freq_max = 1, prev = 1;
    dp[3] = 1, ans[3] = 1;

    for (int i=4; i<MAXN; i++) {
        if (freq_max == 1) {
            dp[i] = dp[i-1] + prev_max;
            freq_max = freq_max + 1; 
        } else {
            dp[i] = dp[i-1] + prev_max + 1;
            freq_max = 1;
            prev_max = prev_max + 1;
        }
        ans[i] = ans[i-1] + dp[i]; 
    }

    int n;
    while (cin >> n)
    {
        if (n < 3) break;

        cout << ans[n-1] << endl;
    }

    return 0;
}