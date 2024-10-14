// https://codejam.lge.com/problem/24431

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
        int n, f, l;
        cin >> n >> f >> l;

        vector<string> str(n);
        for (int i=0; i<n; i++) cin >> str[i];

        unordered_map<string, int> mp;
        int ans = 0;
        for (int i=0; i<n; i++) {
            string suff = str[i].substr(f - l, l);
            if (mp[suff] != 0) {
                ans++;
                mp[suff]--;
            } else {
                mp[suff]++;
            }
        }

        cout << ans << endl;
    }

    return 0;
}