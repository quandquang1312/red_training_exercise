// https://open.kattis.com/problems/presidentialelections

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 2024

int n, total_dele, cons[MAXN], fed[MAXN], unde[MAXN], dele[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n;

    int cons_dele = 0;
    for (int i=0; i<n; i++) {
        cin >> dele[i] >> cons[i] >> fed[i] >> unde[i];
        total_dele += dele[i];
        if (cons[i] + unde[i] > fed[i]) cons_dele += dele[i];
    }

    if (cons_dele <= total_dele / 2) {
        cout << "impossible\n";
    } else {
        // dp[i][j] the minimum need to win
        vector<vector<int>> dp(n + 1, vector<int>(MAXN, 1e9));

        dp[0][0] = 0;
        for (int i=0; i<n; i++) {
            int votes_needed = (cons[i] + fed[i] + unde[i]) / 2 - cons[i] + 1;
            for (int j=0; j<MAXN; j++) {
                if (dp[i][j] == 1e9) continue;
                dp[i+1][j] = min(dp[i][j], dp[i+1][j]);

                if (votes_needed <= unde[i]) {
                    if (j + dele[i] < MAXN) {
                        int addition = max(0LL, votes_needed);
                        dp[i+1][j + dele[i]] = min(dp[i+1][j + dele[i]], dp[i][j] + addition);
                    }
                }
            }
        }

        int ans = 1e9;
        for (int i=total_dele / 2 + 1; i<MAXN; i++) {
            ans = min(ans, dp[n][i]);
        }

        cout << ans << '\n';
    }

    return 0;
}