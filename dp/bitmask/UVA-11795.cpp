// https://vjudge.net/problem/UVA-11795

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<int> cnt, dp;

int tsp(int mask, vector<vector<int>> &wp) {
    if (mask == 0) return 1;
    if (dp[mask] != -1) return dp[mask];

    int ans = 0;
    for (int i=0; i<n; i++) {
        if ((mask & (1 << i)) && cnt[i]) {
            for (int j=0; j<n; j++)
                cnt[j] += wp[i][j];

            ans += tsp(mask ^ (1 << i), wp);

            for (int j=0; j<n; j++)
                cnt[j] -= wp[i][j];
        }
    }

    return dp[mask] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc, t = 1; cin >> tc;
    while (tc--) {
        cin >> n;
        vector<vector<int>> wp(n, vector<int>(n, 0));
        string str; cin >> str;

        cnt.assign(n, 0);
        dp.assign(1 << n, -1);

        for (int i=0; i<n; i++) cnt[i] = str[i] - '0';
        for (int i=0; i<n; i++) {
            cin >> str;
            for (int j=0; j<n; j++)
                wp[i][j] = str[j] - '0';
        }

        int init_mask = (1 << n) - 1;
        int ans = tsp(init_mask, wp);

        cout << "Case " << t << ": " << ans << endl;
        t++;
    }

    return 0;
}