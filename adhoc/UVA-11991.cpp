// https://vjudge.net/problem/UVA-11991

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, q;
    while (cin >> n >> q) {
        map<int, vector<int>> mp;
        for (int i=1, x; i<=n; i++) {
            cin >> x;
            mp[x].push_back(i);
        }

        while (q--) {
            int k, x;
            cin >> k >> x;
            if (mp.find(x) == mp.end()) {
                cout << 0 << "\n";
            } else if (mp[x].size() < k) {
                cout << 0 << "\n";
            } else {
                cout << mp[x][k-1] << '\n';
            }
        }
    }

    return 0;
}
