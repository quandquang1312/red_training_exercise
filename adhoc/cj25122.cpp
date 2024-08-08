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

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];
    
        int j = 0;
        unordered_map<int, int> lst_idx;
        vector<int> lt(n), rt(n);

        for (int i = 0; i < n; i++) {
            if (lst_idx.find(arr[i]) != lst_idx.end() && lst_idx[arr[i]] >= j) {
                j = lst_idx[arr[i]] + 1;
            }
            lst_idx[arr[i]] = i;
            lt[i] = i - j + 1;
        }

        reverse(arr.begin(), arr.end());
        lst_idx.clear();
        j = 0;

        for (int i = 0; i < n; i++) {
            if (lst_idx.find(arr[i]) != lst_idx.end() && lst_idx[arr[i]] >= j) {
                j = lst_idx[arr[i]] + 1;
            }
            lst_idx[arr[i]] = i;
            rt[n-i-1] = i - j + 1;
        }

        int ans = rt[0] + lt[0] - 2;
        for (int i=1; i<n; i++) {
            int r = i + 1, tmp_ans = 0;
            if (lt[i] > 1) tmp_ans += ((1 - binpow(r, lt[i] + 1)) * binpow(1 - r, mod - 2) - 1 - r) % mod, tmp_ans %= mod;
            if (rt[i] > 1) tmp_ans += ((1 - binpow(r, rt[i] + 1)) * binpow(1 - r, mod - 2) - 1 - r) % mod, tmp_ans %= mod;

            ans += tmp_ans;
            ans %= mod;
        }

        cout << ans << '\n';
    }

    return 0;
}