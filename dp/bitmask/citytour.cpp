// https://codejam.lge.com/contest/problem/1322/2

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 9

const int INF = 1e18;

int n;
int D[MAXN][MAXN][MAXN];
int dp[MAXN][1 << MAXN][1 << MAXN];

int dfs(int city, int cityMask, int methodMask, int type) {
    if (dp[city][cityMask][methodMask] != -1) return dp[city][cityMask][methodMask];

    if (cityMask == ((1 << n) - 1)) {
        // looking for the remaining method of transportation
        // to get back to city 1
        int ans = 0;
        for (int j=0; j<n; j++) {
            if (methodMask & (1 << j)) continue;
            ans = D[j][city][0];
        }

        return ans;
    }

    int ans = (type == 0 ? INF : 0);
    // looking for next city
    for (int i=0; i<n; i++) {
        if (city == i) continue;
        if (cityMask & (1 << i)) continue;
        // looking for method of transportation
        for (int j=0; j<n; j++) {
            if (methodMask & (1 << j)) continue;
            if (D[j][city][i] == 0) continue;
            int new_cityMask   = cityMask | (1 << i);
            int new_methodMask = methodMask | (1 << j);
            int next_city_ans = dfs(i, new_cityMask, new_methodMask, type);
            if (next_city_ans == 0) continue; // if the current solution lead to an impossible choice
            int curr_ans = D[j][city][i] + next_city_ans;
            if (type == 0) ans = min(ans, curr_ans);
            else ans = max(ans, curr_ans);
        }
    }

    return dp[city][cityMask][methodMask] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;

        memset(D, 0, sizeof D);
        memset(dp, -1, sizeof dp);

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                for (int k=0; k<n; k++) {
                    cin >> D[i][j][k];
                }
            }
        }

        // find min
        int cityMask = (0 | (1 << 0));
        int ans = dfs(0, cityMask, 0, 0);
        cout << (ans == INF ? 0 : ans) << " ";

        // find max
        memset(dp, -1, sizeof dp);
        ans = dfs(0, cityMask, 0, 1);
        cout << (ans == INF ? 0 : ans) << "\n";
    }

    return 0;
}