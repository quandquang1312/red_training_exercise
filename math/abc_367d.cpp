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

    unordered_map<int, int> mp;

    int curr_remainder = 0, ans = 0;
    for (int i = 1; i <= n * 2; i++)
    {
        curr_remainder = (curr_remainder + arr[i]) % MOD;
        if (mp.find(curr_remainder) == mp.end()) mp[curr_remainder] = i;
        else {
            if (i <= n) ans++; 
            else if (mp[curr_remainder] + n > i) ans++;
        }
    }
    cout << ans << endl;
}
