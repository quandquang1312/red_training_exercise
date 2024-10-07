// https://codeforces.com/contest/2021/problem/B

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, x; cin >> n >> x;

        vector<int> arr(n);
        for (int i=0; i<n; i++)
            cin >> arr[i];

        map<int, int> mp;
        for (auto &e : arr)
            mp[e]++;

        for (auto &[e, f] : mp)
            if (f > 1) mp[e + x] += (f - 1);

        int ans = 0;
        while (1) {
            if (mp.find(ans) == mp.end()) break;
            ans++;
        }

        cout << ans << endl;
    }

    return 0;
}