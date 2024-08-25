// https://codeforces.com/problemset/problem/1066/B

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, r, arr[1010];
    cin >> n >> r;

    vector<pair<int, int>> heaters;
    for (int i=0, x; i<n; i++) {
        cin >> x;
        if (x > 0) heaters.push_back({i - r + 1, i + r - 1});
    }

    if (heaters.size() == 0) {
        cout << "-1\n";
        return 0;
    }

    int k = heaters.size();
    if (heaters[0].first > 0 || heaters[k-1].second < n - 1) {
        cout << "-1\n";
        return 0;
    }

    int ans = 0, lst = 0, upp = -1;
    bool possible = true;
    for (int i=0; i<k && possible; i++) {
        pair<int, int> tmp = heaters[i];
        if (tmp.first <= upp) continue;
        ans++;
        if (tmp.first == upp + 1) upp = tmp.second;
        else {
            if (heaters[i-1].first > upp + 1 || (heaters[i-1].second == upp)) possible = false;
            upp = heaters[i-1].second;
        }
    }

    if (upp < n - 1) ans++;

    cout << (possible ? ans : -1) << endl;

    return 0;
}