// https://cses.fi/problemset/task/1092

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

    int n;
    cin >> n;

    int sm = (n * (n + 1)) / 2;
    if (sm % 2 == 0) {
        cout << "YES\n";
        map<int, int> mp;
        int tmp_sm = sm / 2, idx = n;
        while (tmp_sm - idx > 0 && idx > 0) {
            mp[idx]++;
            tmp_sm -= idx;
            idx--;
        }
        mp[tmp_sm]++;

        cout << mp.size() << "\n";
        for (auto [k, v] : mp) {
            cout << k << " ";
        }
        cout << endl;

        cout << n - mp.size() << '\n';
        for (int i=1; i<=n; i++) {
            if (mp.find(i) == mp.end()) {
                cout << i << " ";
            }
        }
        cout << endl;
    } else {
        cout << "NO\n";
    }

    return 0;
}