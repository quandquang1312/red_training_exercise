// https://atcoder.jp/contests/abc194/tasks/abc194_e

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

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    set<int> ini;
    map<int, int> mp;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        if (i < m) {
            ini.insert(arr[i]);
            mp[arr[i]]++;
        }
    }

    int min_mex = 1e9, prev = 0;
    for (auto &e : ini) {
        if (e != prev && min_mex == 1e9) min_mex = prev;
        prev = prev + 1;
    }

    min_mex = (min_mex == 1e9 ? prev : min_mex);

    int l = 0, r = m;
    while (r < n) {
        mp[arr[l]]--;
        mp[arr[r]]++;
        if (arr[l] < min_mex) {
            if (mp[arr[l]] == 0) {
                min_mex = arr[l];
            }
        }

        l++, r++;
        if (r > n) break;
    }

    cout << min_mex << '\n';

    return 0;
}