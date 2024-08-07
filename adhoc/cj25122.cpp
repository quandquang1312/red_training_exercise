// https://codejam.lge.com/problem/25122

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }

    return res;
}

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

        int arr[n];
        for (int i=0; i<n; i++) cin >> arr[i];
    
        vector<pair<int, int>> ans;
        map<int, int> mp;
        int lst_idx = 0;

        for (int i=0; i<n; i++) {
            if (i == n-1 && mp.find(arr[i]) == mp.end()) {
                ans.push_back({lst_idx, i});
                continue;
            }
            if (mp.find(arr[i]) != mp.end()) {
                if (mp[arr[i]] > lst_idx) ans.push_back({mp[arr[i]], i - 1});
                else ans.push_back({lst_idx, i - 1});
                mp.erase(arr[i]);
                lst_idx = mp[arr[i]];
            }
            mp[arr[i]] = i;
        }

        int sm = 0;
        for (auto &e : ans) {
            int pw = e.second - e.first + 1;
            sm += binpow(e.first, pw) + binpow(e.second, pw);
            sm %= mod;
            cout << e.first << " " << e.second << "\n";
        }

        cout << sm << '\n';
    }

    return 0;
}