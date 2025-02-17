// https://atcoder.jp/contests/abc393/tasks/abc393_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k; cin >> n >> k;

    vector<int> arr(n);
    int max_e = 0;

    for (int i=0; i<n; i++) {
        cin >> arr[i];
        max_e = max(max_e, arr[i]);
    }

    // dp[i] number of multiples of i in the array
    vector<int> cnt(max_e + 1, 0), dp(max_e + 1, 0);
    for (auto &e : arr) cnt[e]++;

    for (int i=1; i<=max_e; i++) {
        for (int j=i; j<=max_e; j += i) {
            dp[i] += cnt[j]; 
        }
    }

    // ans[j] = d, where d is the maximum divisor of j where the number of multiples of d is equal or larger than k
    vector<int> ans(max_e + 1, 1);
    for (int i=1; i<=max_e; i++) {
        if (dp[i] >= k) {
            for (int j=i; j<=max_e; j+=i) {
                ans[j] = max(ans[j], i);
            }
        }
    }

    for (auto &e : arr) {
        cout << ans [e] << "\n";
    }

    return 0;
}