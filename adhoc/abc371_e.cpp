// https://atcoder.jp/contests/abc371/tasks/abc371_e

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

    map<int, vector<int>> mp;
    for (int i=1, x; i<=n; i++) {
        cin >> x;
        if (mp.count(x) == 0) mp[x].push_back(0);
        mp[x].push_back(i);
    }

    for (auto &[k, v] : mp) {
        v.push_back(n + 1);
    }

    int ans = 0;
    vector<int> ex_i(n + 1, 0);
    for (auto &[k, v] : mp) {
        for (int i=1; i<v.size(); i++) {
            int len = (v[i] - v[i-1] - 1);
            if (len > 0) ex_i[k] += (len * (len + 1)) / 2;
        }
        ans += (n * (n + 1)) / 2 - ex_i[k];
    }

    cout << ans << "\n";

    return 0;
}