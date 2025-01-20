// https://atcoder.jp/contests/abc374/tasks/abc374_d

#include <bits/stdc++.h>
using namespace std;

int s, t;

double calcDistance(pair<int, int> a, pair<int, int> b, int tp) {
    double fi = (a.first - b.first);
    double se = (a.second - b.second);
    double ans = (double) (sqrt(fi * fi + se * se));
    if (tp == 0) ans = ans / ((double) s);
    else ans = ans / ((double) t);
    return ans;
}

double solve(int idx, bool f, vector<tuple<pair<int, int>, pair<int, int>>> &lines) {
    int n = lines.size();
    if (idx == n - 1) {
        auto [start_point, end_point] = lines[idx];
        return calcDistance(start_point, end_point, 1);
    }

    auto [start_point, end_point] = lines[idx];
    if (f) swap(start_point, end_point);

    double ans = calcDistance(start_point, end_point, 1);

    auto [nxt_start, nxt_end] = lines[idx + 1];
    double ft = calcDistance(end_point, nxt_start, 0) + solve(idx + 1, false, lines);
    double ff = calcDistance(end_point, nxt_end, 0) + solve(idx + 1, true, lines);

    return min(ft + ans, ff + ans);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n;
    cin >> n >> s >> t;

    vector<tuple<pair<int, int>, pair<int, int>>> lines;
    for (int i=0; i<n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        lines.push_back({{a, b}, {c, d}});
    }

    sort(lines.begin(), lines.end());

    double rs = (double) LONG_LONG_MAX;
    do {
        double se = calcDistance({0, 0}, get<0>(lines[0]), 0);
        double es = calcDistance({0, 0}, get<1>(lines[0]), 0);

        double ans = min(se + solve(0, false, lines), es + solve(0, true, lines));
        rs = min(rs, ans);
    } while (next_permutation(lines.begin(), lines.end()));

    printf("%.10f\n", rs);

    return 0;
}