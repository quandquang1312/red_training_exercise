// https://vjudge.net/problem/UVA-10496

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e12
#define MAXK 15

int dist[MAXK][MAXK], dp[MAXK][1 << MAXK];
int k, n, m;
vector<pair<int, int>> coor;

int distCalc(pair<int, int> p1, pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int tsp(int idx, int mask) {
    if (mask == 0) return dist[idx][0];

    if (dp[idx][mask] != -1) return dp[idx][mask];

    int ans = INF;
    for (int i = 1; i <= k; i++) {
        if (idx == i || (mask & (1 << (i - 1))) == 0)
            continue;
        ans = min(ans, tsp(i, mask ^ (1 << (i - 1))) + dist[idx][i]);
    }

    return dp[idx][mask] = ans;
}

int32_t main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);

    int tc; cin >> tc;

    while (tc--) {
        cin >> m >> n;
        pair<int, int> st;
        cin >> st.first >> st.second;
        cin >> k;

        coor.resize(k+1);

        coor[0] = st;
        for (int i=1; i<=k; i++) cin >> coor[i].first >> coor[i].second;

        for (int i=0; i<=k; i++) {
            for (int j=i+1; j<=k; j++) {
                dist[i][j] = distCalc(coor[i], coor[j]);
                dist[j][i] = dist[i][j];
            }
        }

        memset(dp, -1, sizeof(dp));

        int ans = INF;
        int mask = ((1 << k) - 1);
        for (int i=1; i<=k; i++) {
            ans = min(ans, tsp(i, mask ^ (1 << (i - 1))) + dist[0][i]);
        }

        cout << ans << endl;
    }

    return 0;
}