// https://codeforces.com/problemset/problem/1398/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

#ifndef MAXN
#define MAXN 200100
#endif

int n, arr[MAXN], diff[MAXN];

void update(int l, int r, int vl) {
    diff[l] += vl;
    if (r + 1 < n) diff[r] -= vl;
}

void apply_update()
{
    /*
    // update the value of arr by the prefix sum of diff
    */
    for (int i=0; i<n; i++) diff[i] += diff[i-1];
    for (int i=0; i<n; i++) arr[i] += diff[i]; 
}

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

        string str; cin >> str;
        str = ' ' + str;
        vector<int> prefix_sum(n + 1, 0);
        vector<int> suffix_sum(n + 1, 0);

        for (int i=1; i<=n; i++) prefix_sum[i] += prefix_sum[i-1] + (str[i] - '0');
        int sm = 0;
        for (int i=n; i>=1; i--) {
            int val = str[i] - '0';
            sm += val;
            suffix_sum[i] = sm + i; 
        }

        int ans = 0;
        map<int, int> mp;
        for (int i=1; i<=n; i++) {
            mp[suffix_sum[i]]++;
            int val = i - (str[i] - '0') + 1;
            val += (prefix_sum[n] - prefix_sum[i - 1]);
            if (mp.find(val) != mp.end()) {
                ans += mp[val];
            }
        }

        cout << ans << "\n";
    }

    return 0;
}