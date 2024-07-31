// https://vjudge.net/problem/UVA-216

#include <bits/stdc++.h>
using namespace std;

int n;
double min_len;
vector<int> trace, tmp_trace;
vector<vector<double>> dp;

inline double sqr(int p) { return (double)(p * p); }

double tsp(int idx, int mask, vector<vector<double>>& dist, double len) {
    if (mask == 0) {
        if (len < min_len) {
            min_len = len;
            for (int i=0; i<n; i++) trace[i] = tmp_trace[i];
        }

        return 0.0;
    }

    if (dp[idx][mask] != -1.0) {
        if (len + dp[idx][mask] < min_len) {
            min_len = len + dp[idx][mask];
            int connected =  n - __builtin_popcount(mask);
            for (int i=0; i<connected; i++) trace[i] = tmp_trace[i];
        }
        return dp[idx][mask];
    }

    double ans = (double) INT_MAX;
    for (int i=0; i<n; i++) {
        if (mask & (1 << i)) {
            int connected =  n - __builtin_popcount(mask);
            tmp_trace[connected] = i;
            double tsp_rs = tsp(i, mask ^ (1 << i), dist, len + dist[idx][i]) + dist[idx][i];
            if (ans > tsp_rs) {
                ans = tsp_rs;
                for (int i=0; i<n; i++) trace[i] = tmp_trace[n-i-1];
            }
        }
    }

    return dp[idx][mask] = ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int t = 1;
    while (cin >> n) {
        if (n == 0) break;
        printf("**********************************************************\n");
        printf("Network #%d\n", t); t++;

        trace.assign(n, -1);
        tmp_trace.assign(n, -1);
        dp.assign(n, vector<double>(1 << n, -1.0));
        min_len = (double) INT_MAX;

        vector<pair<int, int>> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i].first >> arr[i].second;

        auto calDist = [](pair<int, int> p1, pair<int, int> p2) -> double {
            double ret = sqrt(sqr(abs(p1.first - p2.first)) + sqr(abs(p1.second - p2.second))) + 16.0;
            return (double) ret;
        };

        vector<vector<double>> dist(n, vector<double>(n, 0.0));
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                dist[i][j] = calDist(arr[i], arr[j]);
                dist[j][i] = dist[i][j];
            }
        }

        int init_mask = ((1 << n) - 1);
        double ans = (double) INT_MAX;
        for (int i=0; i<n; i++) {
            tmp_trace[0] = i;
            ans = min(ans, tsp(i, init_mask ^ (1 << i), dist, 0.0));
        }

        for (int i = 0; i < n - 1; i++) {
            int x1 = arr[trace[i]].first, y1 = arr[trace[i]].second;
            int x2 = arr[trace[i + 1]].first, y2 = arr[trace[i + 1]].second;
            printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n",
                x1, y1, x2, y2, dist[trace[i]][trace[i + 1]]);
        }
        printf("Number of feet of cable required is %.2lf.\n", ans);
    }

    return 0;
}