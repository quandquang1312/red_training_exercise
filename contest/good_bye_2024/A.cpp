// https://codeforces.com/contest/2053/problem/A

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
        int n; cin >> n;
        vector<int> arr(n);

        bool possible = false;
        for (int i=0; i<n; i++) {
            cin >> arr[i];
            if (i) {
                if (arr[i] * 2 > arr[i-1] && arr[i-1] * 2 > arr[i]) possible = true;
            }
        }

        cout << (possible ? "YES" : "NO") << "\n";
    }

    return 0;
}