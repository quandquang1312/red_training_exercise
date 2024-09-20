// https://open.kattis.com/problems/safepassage?tab=metadata

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n;
vector<int> times, dp;

vector<pair<int, int>> possible_pair(int mask) {
    vector<pair<int, int>> rs;
    for (int i=0; i<n; i++) {
        if (mask & (1 << i)) continue;
        for (int j=i+1; j<n; j++) {
            if (mask & (1 << j)) continue;
            int new_mask = mask | (1 << i);
            new_mask = new_mask | (1 << j);
            rs.push_back({i, j});
        }
    }

    return rs;
}

int min_at_dorm(int mask) {
    int rs = INF, pos = -1;
    for (int i=0; i<n; i++) {
        if (!(mask & (1 << i))) continue; // not get back to dorm yet
        if (rs > times[i]) {
            rs = times[i];
            pos = i;
        }
    }

    return pos;
}

int dfs(int mask) {
    if (dp[mask] != -1) return dp[mask];

    int no_remain = n - __builtin_popcount(mask);
    if (no_remain <= 2) {
        int rs = 0;
        for (int i=0; i<n; i++) {
            if (!(mask & (1 << i))) rs = max(rs, times[i]);
        }

        return rs;
    }

    vector<pair<int, int>> curr = possible_pair(mask);

    int ans = INF;
    for (auto &[i, j] : curr) {
        int new_mask = mask | (1 << i);
        new_mask = new_mask | (1 << j);

        // the pupil has min times has to get back to return the cloak
        int min_one = min_at_dorm(new_mask);
        new_mask = new_mask ^ (1 << min_one);

        // ans is a random pupil i-th and j-th plus the times for the min pupil time
        // to get back + ans at the remaining pupils
        int tmp_ans = max(times[i], times[j]) + times[min_one] + dfs(new_mask);
        ans = min(ans, tmp_ans);
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

    cin >> n;
    times.assign(n, 0);
    dp.assign((1 << n) + 1, -1);

    for (int i=0; i<n; i++) cin >> times[i];

    int init_mask = 0;
    int ans = dfs(init_mask);
    cout << ans << "\n";

    #ifdef DEBUG
        vector<pair<int, int>> tmp = possible_pair(init_mask);
        for (auto &[i, j] : tmp) {
            cout << i << " - " << j << endl;
        }
    #endif

    return 0;
}