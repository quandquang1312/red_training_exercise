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

    sort(arr.begin(), arr.end(), [](pair<int, int> p1, pair<int, int> p2) {
        return p1.second < p2.second;
    });

    int ans = -1;
    for (int i=0; i<n; i++) {
        
        int sm = arr[i].first;
        for (int j=i+1; j < n; j++) {
            if (arr[j].second - arr[i].second < 9)
                sm += arr[j].first;
            else break;
        }

        int rm = 24 - arr[i].second;
        if (rm > 9) continue;

        for (int j=0; arr[j].second < rm; j++) {
            sm += arr[j].first;
        }

        ans = max(ans, sm);
    }

    cout << ans << endl;

    return 0;
}