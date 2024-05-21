// https://codejam.lge.com/problem/28096

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e12
#define MAXN 16

int f, w, l, n;
vector<tuple<int, int, int>> points;
int dist[MAXN][MAXN], dp[MAXN][1 << MAXN];

int findMin(int a, int b, int c, int d) {
    int minab = min(a,b);
    int mincd = min(c,d);
    return min(minab, mincd);
}

int distCalc(tuple<int, int, int> t1, tuple<int, int, int> t2) {
    int ans = 0;

    if (get<2>(t1) == get<2>(t2)) // same floor
    {
        ans += (abs(get<0>(t1) - get<0>(t2)) + abs(get<1>(t1) - get<1>(t2)));
    } else { // diff floor
        int t1_e1 = abs(get<0>(t1) - 1) + abs(get<1>(t1) - 1), t2_e1 = abs(get<0>(t2) - 1) + abs(get<1>(t2) - 1);
        int t1_e2 = abs(get<0>(t1) - w) + abs(get<1>(t1) - 1), t2_e2 = abs(get<0>(t2) - w) + abs(get<1>(t2) - 1);
        int t1_e3 = abs(get<0>(t1) - 1) + abs(get<1>(t1) - l), t2_e3 = abs(get<0>(t2) - 1) + abs(get<1>(t2) - l);
        int t1_e4 = abs(get<0>(t1) - w) + abs(get<1>(t1) - l), t2_e4 = abs(get<0>(t2) - w) + abs(get<1>(t2) - l);

        ans = findMin(t1_e1 + t2_e1, t1_e2 + t2_e2, t1_e3 + t2_e3, t1_e4 + t2_e4);

        if (get<2>(t1) < get<2>(t2)) {
            ans += (2 * (get<2>(t2) - get<2>(t1)));
        } else if (get<2>(t1) > get<2>(t2)) {
            ans += ((get<2>(t1) - get<2>(t2)));
        }
    }

    return ans;
}

int tsp(int idx, int mask)
{
    if (mask == 0) return 0;

    if (dp[idx][mask] != -1) return dp[idx][mask];

    int ans = INF;
    for (int i=1; i<=n; i++) {
        if (i == idx || (mask & (1 << i)) == 0) continue;
        int new_mask = (mask ^ (1 << i));
        ans = min(ans, tsp(i, new_mask) + dist[idx][i]);
    }

    return dp[idx][mask] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);

    int tc; cin >> tc;
    while (tc--)
    {
        points.clear();
        memset(dp, -1, sizeof(dp));

        cin >> f >> w >> l >> n;

        int sz, sx, sy;
        for (int i=0; i<=n; i++) {
            cin >> sz >> sx >> sy;
            points.push_back(make_tuple(sx, sy, sz));
        }

        for (int i=0; i<=n; i++)
            for (int j=0; j<=n; j++)
                dist[i][j] = INF;


        for (int i=0; i<=n; i++) {
            for (int j=0; j<=n; j++) {
                if (i == j) continue;
                dist[i][j] = distCalc(points[i], points[j]);
            }
        }

        int mask = ((1 << (n + 1)) - 1) ^ (1 << 0);
        int ans = INF;
        for (int i=1; i<=n; i++) {
            int tmp = tsp(i, mask ^ (1 << i)) + dist[0][i];
            ans = min(ans, tmp);
        }

        cout << ans << endl;
    }

    return 0;
}