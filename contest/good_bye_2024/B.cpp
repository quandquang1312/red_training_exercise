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
        vector<pair<int, int>> arr(n);
        vector<int> marked(2 * (n + 1), 0), prefix(2 * (n + 1), 0);
        vector<int> prefix_marked(2 * (n + 1), 0);

        for (int i=0, l, r; i<n; i++) {
            cin >> l >> r;
            if (l == r) {
                prefix[l] += 1;
                marked[l] = 1;
            }
            arr[i] = {l, r};
        }

        for (int i=0; i<=2*n; i++) {
            prefix[i+1] += prefix[i];
            prefix_marked[i+1] = prefix_marked[i] + (marked[i+1] == 0);
        }

        // for (int i=0; i<=2*n; i++) {
        //     cout << i << ": " << marked[i] << " - "g << prefix_marked[i] << "\n";
        // }

        for (int i=0; i<n; i++) {
            auto [l, r] = arr[i];

            if (l == r) {
                int sm = prefix[r] - prefix[l-1];
                if (sm > 1) cout << "0";
                else cout << "1";
            } else {
                int not_marked = prefix_marked[r] - prefix_marked[l-1];
                if (not_marked) cout << "1";
                else cout << "0";
            }
        }

        cout << "\n";
    }

    return 0;
}