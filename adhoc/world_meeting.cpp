// https://atcoder.jp/contests/abc325/tasks/abc325_b

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<pair<int, int>> arr(n);

    for (auto &e : arr)
        cin >> e.first >> e.second;

    int premap[24];

    for (int i=0; i<24; i++)
        premap[i] = (i+9) % 24;

    int ans = -1;
    for (int i=0; i<24; i++) {
        int sm = 0;
        for (int j=0; j<n; j++) {
            if (i < premap[i]) {
                if (i < premap[i] && (arr[j].second >= i && arr[j].second < premap[i])) {
                    sm += arr[j].first;
                    // cout << i << "-" << j << " cp1\n";
                }
            } else {
                if (arr[j].second >= i) {
                    sm += arr[j].first;
                } else if (arr[j].second < premap[i]) {
                    sm += arr[j].first;
                }
            }
        }

        // cout << i << ": " << sm << endl;

        ans = max(ans, sm);
    }

    cout << ans << endl;

    return 0;
}