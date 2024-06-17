// https://atcoder.jp/contests/dp/tasks/dp_o?lang=en

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 22
const int MOD = 1e9 + 7;
int n, arr[MAXN][MAXN], dp[MAXN][1 << MAXN];

// match idx-th men with the women available in the mask
// first idx - 1 men already paired with the women that are 0s in the mask)
int solve(int idx, int mask)
{
    if (idx == n) return 1;

    if (dp[idx][mask] != -1) return dp[idx][mask];

    int ans = 0;
    for (int j=0; j<n; j++) {
        if (arr[idx][j] == 1 && ((mask & (1 << j)) != 0)) {
            int new_mask = mask ^ (1 << j);
            ans += solve(idx+1, new_mask);
            ans %= MOD;
        }
    }

    return dp[idx][mask] = ans;
}

void solve_bottom()
{
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int men=0; men<n; men++) {
        for (int mask=0; mask < (1 << n); mask++) {

            // if the mask with men is not fit, then it's not a valid dp[men][mask]
            if (__builtin_popcount(mask) != men) continue;
            for (int women=0; women<n; women++) {
                if (arr[men][women] == 1 && !(mask & (1 << women))) {
                    // if men-women are compatible and the women has not been choosen
                    // then we add 1 to the state where
                    // we choose the women for the men+1 with the mask exclude that women
                    dp[men+1][mask | (1 << women)] += dp[men][mask] % MOD;
                    dp[men+1][mask | (1 << women)] %= MOD;
                }
            }
        }
    }

    cout << dp[n][(1 << n) - 1] << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> arr[i][j];
        }
    }

    if (false) 
    {
        memset(dp, -1, sizeof dp);
        int init_mask = (1 << n) - 1;
        int ans = solve(0, init_mask);

        cout << ans << endl;
    } else {
        solve_bottom();
    }

    return 0;
}