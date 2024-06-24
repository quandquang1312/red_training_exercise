// https://open.kattis.com/contests/hzsvhn/problems/walrusweights

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

    int n; cin >> n;
    int arr[n+1];

    for (int i=0; i<n; i++) cin >> arr[i];

    bool dp[2005] {};

    dp[0] = 1;
    for (int i=0; i<n; i++) {
        for (int j=2000; j >= arr[i]; j--) {
            dp[j] |= dp[j-arr[i]];
        }
    }

    if (dp[1000]) {
        cout << 1000 << endl;
    } else {
        int closest = 1e9;
        for (int i=1001; i<=2000; i++) { 
            if (dp[i]) {
                closest = i;
                break;
            }
        }

        for (int i=999; (1000 - i < closest); i--) {
            if (dp[i]) {
                if (1000 - i < (closest - 1000)) {
                    closest = i;
                }
                break;
            }
        }

        cout << closest << endl;
    }

    return 0;
}