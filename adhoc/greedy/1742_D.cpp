// https://codeforces.com/problemset/problem/1742/D

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
        vector<int> max_pos(1010, -1);
        for (int i=0; i<n; i++) {
            cin >> arr[i];
            max_pos[arr[i]] = i + 1; 
        }

        int ans = -1;
        for (int i=1; i<=1000; i++) {
            if (max_pos[i] == -1) continue;
            for (int j=i; j<=1000; j++) {
                if (max_pos[j] != -1 && __gcd(i, j) == 1) {
                    ans = max(ans, max_pos[i] + max_pos[j]);
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}