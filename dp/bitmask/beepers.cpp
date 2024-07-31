// https://open.kattis.com/problems/beepers?tab=metadata

#include <bits/stdc++.h>
using namespace std;

int tsp(int n, vector<vector<int>>& dist) {
    vector<vector<int>> dp(n, vector<int>(1 << n, 1e9));

    for (int i = 0; i < n; i++) dp[i][1 << i] = dist[0][i];

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;
            for (int j = 0; j < n; j++) {
                if (i == j || !(mask & (1 << j))) continue;
                dp[i][mask] = min(dp[i][mask], dp[j][mask ^ (1 << i)] + dist[i][j]);
            }
        }
    }

    int ans = 1e9;
    for (int i = 1; i < n; i++) {
        ans = min(ans, dp[i][(1 << n) - 1] + dist[0][i]);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc;
    cin >> tc;
    while (tc--) {
        int x, y, n; cin >> x >> y;

        pair<int, int> st;
        cin >> st.first >> st.second;
    
        cin >> n;
        n++;

        vector<pair<int, int>> beeper(n);
        beeper[0] = st;

        for (int i=1; i<n; i++) cin >> beeper[i].first >> beeper[i].second;
        vector<vector<int>> dist(n, vector<int>(n, 0));

        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                dist[i][j] = abs(beeper[i].first - beeper[j].first) + abs(beeper[i].second - beeper[j].second);
                dist[j][i] = dist[i][j];
            }
        }

        int ans = tsp(n, dist);
        cout << ans << endl;
    }

    return 0;
}