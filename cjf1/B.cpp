#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<int> alb, bob;
int n, m;
int dp[1<<16][16];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m;

        memset(dp, 0, sizeof dp);

        alb.resize(n);
        for (int i=0; i<n; i++) cin >> alb[i];

        for (int i=-n; i<=n; i++) {
            if (i == 0) continue;
            if (find(alb.begin(), alb.end(), i) == alb.end()) {
                bob.push_back(i);
            }
        }

        dp[(1 << n) - 1][0] = 1;
        for (int mask=((1 << n) - 1); mask >= 0; mask--) {
            for (int i=0; i<n; i++) {
                if (!(mask & (1 << i))) continue;
                int idx = n - __builtin_popcount(mask);
                for (int score = 0; score <= m; score++) {
                    if (score > idx) continue;
                    int new_score = score;
                    if (alb[idx] * bob[i] < 0) new_score += 1;
                    else if (abs(alb[idx]) > abs(bob[i])) new_score += 1;

                    dp[mask ^ (1 << i)][new_score] += dp[mask][score];
                }
            }
        }

        cout << dp[0][m] << endl;

        bob.clear();
        alb.clear();
    }

    return 0;
}