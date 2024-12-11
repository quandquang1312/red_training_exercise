// https://vjudge.net/contest/678673#problem/J

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e18

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, x; 
    cin >> n >> m >> x;
    
    vector<int> cost(n, 0);
    vector<vector<int>> arr(n, vector<int>(m, 0));

    bool possible = true;

    for (int i=0; i<n; i++) {
        cin >> cost[i];
        for (int j=0; j<m; j++)
            cin >> arr[i][j];
    }

    for (int j=0; j<m && possible; j++) {
        int cur = 0;
        for (int i=0; i<n; i++) {
            cur += arr[i][j];
        }
        if (cur < x) possible = false;
    }

    if (!possible) {
        cout << "-1\n";
    } else {
        int ans = INF;
        for (int i=0; i < (1 << n); i++) {
            possible = true;
            vector<int> cur(m, 0);
            int cur_cost = 0;
            for (int j=0; j<n; j++) {
                if (i & (1 << j)) { // buy j-th book
                    for (int k=0; k<m; k++)
                        cur[k] += arr[j][k];
                    cur_cost += cost[j];
                }
            }

            for (int k=0; k<m && possible; k++)
                if (cur[k] < x) possible = false;
            if (possible) ans = min(ans, cur_cost);
        }

        cout << ans << "\n";
    }

    return 0;
}