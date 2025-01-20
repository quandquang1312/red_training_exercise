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

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];

        int mp[11] {};

        int bound = (n % 2 == 0 ? n : n - 1);
        for (int i=0; i<bound; i++) {
            mp[arr[i]]++;
        }

        int ans = 0;
        for (int j=1; j<=n; j+=2) {
            ans += n - j + 1;
        }

        cout << "ans: " << ans << "\n";

        for (int i=0; i<bound; i+=2) {
            int sm = 0;
            int median_pos_lo = (bound - i) / 2;
            int median_pos_hi = (bound - i) / 2 + 1;
            for (int j=1; j<=10; j++) {
                sm += mp[j];
                if (sm == median_pos_lo && sm < median_pos_hi) break;
                if (sm >= median_pos_hi) {
                    ans++;
                    break;
                }
            }
            mp[arr[i]]--;
            mp[arr[i+1]]--;
        }

        cout << ans << "\n";
    }

    return 0;
}