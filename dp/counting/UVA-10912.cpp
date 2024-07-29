// https://vjudge.net/problem/UVA-10912

#include <bits/stdc++.h>
using namespace std;

int N, S, dp[30][400][30];

int solve(int remain, int sm, int prev) {
    if (remain == 0) return sm == S;
    if (sm >= S) return 0;
    if (dp[remain][sm][prev] != -1) return dp[remain][sm][prev];

    int ans = 0;
    for (int i=prev+1; i<=26; i++) ans += solve(remain-1, sm+i, i);
    return dp[remain][sm][prev] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc = 1;
    while (cin >> N >> S) {
        if (N == 0 && S == 0) break;
        memset(dp, -1, sizeof dp);

        int ans;
        if (N > 26 || S > 351) ans = 0;
        else {
            // ans = solve(N, 0, 0);

            for (int i=2; i<=N; i++) {
                for (int prev=0; prev<=26; prev++) {
                    for (int sm=0; sm<=355; sm++) {
                        dp[rm][sm][prev] += dp[rm-1][sm-rm][prev];
                    }
                }
            }
        }

        cout << "Case " << tc << ": " << ans << '\n';
        tc++;
    }

    return 0;
}