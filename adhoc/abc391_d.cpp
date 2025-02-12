// https://atcoder.jp/contests/abc391/tasks/abc391_d

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, w; cin >> n >> w;

    vector<pair<int, int>> loc(n + 1);

    vector<vector<pair<int, int>>> each_cols(w + 1);
    for (int i=1; i<=n; i++) {
        cin >> loc[i].first >> loc[i].second;
        each_cols[loc[i].first].push_back({loc[i].second, i});
    }

    int min_row = INF;
    for (int i=1; i<=w; i++) {
        sort(each_cols[i].begin(), each_cols[i].end());
        min_row = min(min_row, (int) each_cols[i].size());
    }

    vector<int> min_time_row(min_row, 0);
    vector<int> ans(n + 1, INF);
    for (int r=0; r<min_row; r++) {
         for (int c=1; c<=w; c++) {
            min_time_row[r] = max(min_time_row[r], each_cols[c][r].first);
        }

        for (int c=1; c<=w; c++) {
            int idx = each_cols[c][r].second;
            ans[idx] = min_time_row[r];
        }
    }

    int q; cin >> q;
    while (q--) {
        int t, x; cin >> t >> x;
        cout << (ans[x] > t ? "Yes" : "No") << "\n"; 
    }

    return 0;
}