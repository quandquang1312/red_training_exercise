// https://vjudge.net/problem/UVA-12324

#include <bits/stdc++.h>
using namespace std;

int n;
int dp[110][110];

int solve(int idx, int sphere_left, vector<pair<int, int>>& trip) {
    if (idx > n) return 0;
    if (dp[idx][sphere_left] != -1) return dp[idx][sphere_left];

    auto [t, b] = trip[idx];

    // not use sphere for this trip
    int not_use = t + solve(idx+1, min(n, sphere_left + b), trip);
    
    // use a sphere for this trip
    int use     = 1e9;
    if (sphere_left > 0) use = t/2 + solve(idx+1, min(n, sphere_left + b - 1), trip);

    return dp[idx][sphere_left] = min(not_use, use); 
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    while (cin >> n) {
        if (!n) break;

        vector<pair<int, int>> trip(n+1);
        for (int i=1; i<=n; i++) cin >> trip[i].first >> trip[i].second;

        memset(dp, -1, sizeof dp);
        int ans = solve(1, 0, trip);

        cout <<  ans << endl;
    }

    return 0;
}