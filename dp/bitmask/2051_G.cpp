// https://codeforces.com/contest/2051/problem/G

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, 0));

    vector<pair<int, char>> queries(q);
    for (int i=0, x; i<q; i++) {
        char c; cin >> x >> c;
        queries[i] = {x, c};
    }

    for (int x=1; x<=n; x++) {
        for (int y=1; y<=n; y++) {
            if (x == y) continue;
            string str;
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

            cout << x << "->" << y << ": " << dist[x][y] << "\n";
        }
    }

    return 0;
}