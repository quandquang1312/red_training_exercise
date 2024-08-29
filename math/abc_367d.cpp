// https://atcoder.jp/contests/abc367/tasks/abc367_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, MOD;
    cin >> n >> MOD;
    vector<int> arr(n * 2 + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        arr[i + n] = arr[i];
    }

    vector<int> presum(n * 2 + 1, 0);
    for (int i=1; i <= (n * 2); i++) {
        presum[i] = presum[i-1] + arr[i];
    }

    int ans = 0;
    for (int i=1; i<=n; i++) {
        for (int j=i; j<i+n; j++) {
            if ((presum[j] - presum[i - 1]) % MOD == 0) {
                ans++;
                // cout << i << " -> " << j << "\n";
            }
        }
    }

    cout << ans << '\n';

    // unordered_map<int, int> mp;

    // int curr_remainder = 0, ans = 0;
    // mp[0] = 1;

    // vector<int> remainder(n * 2 + 1, 0);
    // for (int i = 1; i <= (n * 2); i++)
    // {
    //     curr_remainder = (curr_remainder + (arr[i] % MOD)) % MOD;
    //     remainder[i] = curr_remainder;
    //     if (mp.find(curr_remainder) != mp.end()) {
    //         if (i - mp[curr_remainder] <= n) {
    //             ans += mp[curr_remainder];
    //             cout << mp[curr_remainder] + 1 << " => " << i  << '\n';
    //         }
    //     }
    //     if (i <= n) mp[curr_remainder]++;
    //     else mp[remainder[i - n]]--;
    // }
    // cout << ans << endl;

    return 0;
}
