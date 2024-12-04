// https://codeforces.com/contest/977/problem/F

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e13;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);

    for (int i=0; i<n; i++) cin >> arr[i];

    map<int, int> mp;
    vector<int> dp(n + 1, 1);

    int max_dp = 1, max_pos = arr[0];
    for (int i=0; i<n; i++) {
        if (mp.find(arr[i]-1) != mp.end()) {
            int idx = mp[arr[i]-1];
            dp[i] = dp[idx] + 1;
            if (dp[i] > max_dp) {
                max_dp = dp[i];
                max_pos = arr[i];
            }
        }
        mp[arr[i]] = i;
    }

    cout << max_dp << "\n";
    int starting = max_pos - max_dp + 1;
    for (int i=0; i<n; i++) {
        if (arr[i] == starting) {
            cout << i + 1 << " ";
            starting++;
        }
        if (starting > max_pos) break;
    }
    cout << "\n";

    return 0;
}