// https://codeforces.com/contest/1316/problem/E

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

    int n, p, k; 

    cin >> n >> p >> k;

    int audience[n], s[n+1][p+1], idxSorted[n+1];
    int dp[n+1][1 << (p+1)];

    for (int i=0; i<n; i++) cin >> audience[i];
    for (int i=0; i<n; i++) {
        for (int j=0; j<p; j++)
            cin >> s[i][j];
    }

    for (int i=0; i<n; i++)
        idxSorted[i] = i;

    sort(idxSorted, idxSorted+n, [&](int i, int j){
        return audience[i] > audience[j]; 
    });

    // cout << "audience: ";
    // for (int i=0; i<n; i++) {
    //     cout << audience[idxSorted[i]] << " ";
    // } cout << endl;

    // cout << "strength: \n";
    // for (int i=0; i<n; i++) {
    //     for (int j=0; j<p; j++)
    //         cout << s[idxSorted[i]][j] << " ";
    //     cout << endl;
    // }

    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    for (int i=1; i<=n; i++) {

        int x = idxSorted[i-1];

        for (int mask=0; mask < (1 << p); mask++) {
            // not choose this man to be a players or audience
            if (dp[i-1][mask] != -1) dp[i][mask] = dp[i-1][mask]; 
            for (int j=0; j<p; j++) {
                if ((mask & (1 << j)) && dp[i-1][mask ^ (1 << j)] != -1)
                {
                    // choose this man to be a players
                    dp[i][mask] = max(dp[i][mask], dp[i-1][mask ^ (1 << j)] + s[x][j]);
                }
            }

            int n_players = __builtin_popcount(mask);
            int current_audience = i - 1 - n_players;

            if (current_audience < 0) continue;
 
            if (current_audience < k)
            {
                // choose this man to be a audience
                if (dp[i-1][mask] != -1)
                    dp[i][mask] = max(dp[i][mask], dp[i-1][mask] + audience[x]);
            }
        }
    }

    cout << dp[n][(1 << p) - 1] << endl;

    return 0;
}