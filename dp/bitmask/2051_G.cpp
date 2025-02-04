// https://codeforces.com/contest/2051/problem/G

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;

vector<vector<int>> dp, dist;
vector<int> last_length;
int n;

int tsp() {
    int ans = INF;

    for (int i=0; i<n; i++)
        dp[1 << i][i] = 0;

    for (int mask=1; mask<(1 << n); mask++) {
        for (int i=0; i<n; i++) {
            if (!(mask & (1 << i))) continue;
            for (int j=0; j<n; j++) {
                if (i == j) continue;
                if (!(mask & (1 << j))) continue;
                int prev_mask = mask ^ (1 << i);
                dp[mask][i] = min(dp[mask][i], dist[j][i] + dp[prev_mask][j]);
            }
        }
    }

    for (int i=0; i<n; i++)
        ans = min(ans, dp[(1 << n) - 1][i] + last_length[i]);

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int q; cin >> n >> q;

    dp.assign(1 << n, vector<int>(n, INF));
    dist.assign(n, vector<int>(n, 0));
    last_length.assign(n, 0);

    vector<pair<int, char>> queries(q);
    for (int i=0, x; i<q; i++) {
        char c; cin >> x >> c;
        x--;
        queries[i] = {x, c};
        if (c == '+') last_length[x]++;
    }

    for (int x=0; x<n; x++) {
        for (int y=0; y<n; y++) {
            if (x == y) continue;
            int cur_m = 0;
            for (int i=0; i<q; i++) {
                if (queries[i].first == x && queries[i].second == '+') {
                    if (cur_m) cur_m--;
                    else dist[x][y]++;
                }

                if (queries[i].first == y && queries[i].second == '-') {
                    cur_m++;
                }
            }
        }
    }

    int ans = tsp();

    cout << n + ans << "\n";

    return 0;
}