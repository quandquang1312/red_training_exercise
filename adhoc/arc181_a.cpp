// https://atcoder.jp/contests/arc181/tasks/arc181_a

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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> arr(n+1);

        bool sorted = true, fi = false;
        int mmax = 0;
        for (int i=1; i<=n; i++) {
            cin >> arr[i];
            sorted &= (arr[i] == i);
            mmax = max(mmax, arr[i]);
            if (mmax <= i && arr[i] == i) fi = true;
        }

        if (sorted) {
            cout << "0\n";
        } else {
            if (fi) cout << "1\n";
            else if (arr[1] == n && arr[n] == 1) cout << "3\n";
            else cout << "2\n";
        }
    }

    return 0;
}