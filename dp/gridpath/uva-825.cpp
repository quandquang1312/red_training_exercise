// https://vjudge.net/problem/UVA-825

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    for (int d=0; d<tc; d++) {
        int n, m;
        cin >> n >> m;
        vector<vector<bool>> safe(n+1, vector<bool>(m+1, true));

        string s;
        getline(cin, s);

        for (int i=1; i<=n; i++) {
            getline(cin, s);
            stringstream sin(s);
            int p, q; sin >> p;
            while (sin >> q) {
                safe[p][q] = false;
            }
        }

        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        dp[1][1] = 1;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (i == 1 && j == 1) continue;
                if (safe[i-1][j]) dp[i][j] += dp[i-1][j];
                if (safe[i][j-1]) dp[i][j] += dp[i][j-1];
            }
        }

        cout << dp[n][m] << endl;
        if (d < tc - 1) cout << endl;
    }

    return 0;
}