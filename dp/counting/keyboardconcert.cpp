// https://open.kattis.com/problems/keyboardconcert

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

    int n, m;
    cin >> n >> m;
    
    vector<int> tune(m+1);
    vector<vector<int>> note(m+1);
    for (int i=1; i<=n; i++) {
        int x, tmp; cin >> x;
        while (x--) {
            cin >> tmp;
            note[tmp].push_back(i);
        }
    }

    for (int i=1; i<=m; i++) cin >> tune[i];

    vector<vector<int>> dp(m+1, vector<int>(n+1, 1e9));
    
    for (int i=1; i<=n; i++) {
        for (auto &e : note[tune[1]]) dp[1][e] = 0;
    }

    int min_lst = 0;
    for (int i=2; i<=m; i++) {
        int current_note = tune[i];

        int min_tmp = 1e9;
        for (auto &intr : note[current_note]) {
            if (dp[i-1][intr] != 1e9) dp[i][intr] = min(dp[i][intr], dp[i-1][intr]);
            else dp[i][intr] = min(dp[i][intr], min_lst + 1);

            min_tmp = min(min_tmp, dp[i][intr]);
        }

        min_lst = min_tmp;
    }

    int ans = 1e9;
    for (int i=1; i<=n; i++) {
        ans = min(ans, dp[m][i]);
    }

    cout << ans << endl;

    return 0;
}