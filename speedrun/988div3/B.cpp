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
        int k; cin >> k;

        vector<int> arr(k);
        for (int i=0; i<k; i++) cin >> arr[i];

        unordered_map<int, int> mp;
        for (int i=0; i<k; i++) {
            if ((k - 2) % arr[i] == 0) {
                if (mp.find((k - 2) / arr[i]) != mp.end()) {
                    cout << arr[i] << " " << (k - 2) / arr[i] << "\n";
                    break;
                }
            }
            mp[arr[i]]++;
        }
    }

    return 0;
}