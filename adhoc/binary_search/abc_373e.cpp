// https://atcoder.jp/contests/abc373/tasks/abc373_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m, k;
vector<pair<int, int>> arr;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> m >> k;
    arr.resize(n);

    vector<int> f(n);

    int rm = 0;

    for (int i=0; i<n; i++) {
        cin >> arr[i].first;
        f[i] = arr[i].first;
        rm += arr[i].first;
        arr[i].second = i;
    }

    rm = k - rm;

    cout << "rm: " << rm <<"\n";

    // sort(arr.begin(), arr.end());
    sort(f.begin(), f.end());

    for (int i=0; i<n; i++) {
        int l = 0, r = rm;

        int pos = upper_bound(f.begin(), f.end(), arr[i].first + r) - f.begin();
        int gr = n - pos;

        if (gr >= m) {
            cout << "-1 ";
        } else {
            // impl
            while (l < r) {
                int mid = (l + r) >> 1;
                int pos_mid = lower_bound(f.begin(), f.end(), arr[i].first + mid) - f.begin();
                int gr_pos = n - pos_mid;
                if (gr_pos < m) r = mid;
                else l = mid + 1;
            }
            cout << l << " ";
        }
    }

    cout << "\n";


    return 0;
}