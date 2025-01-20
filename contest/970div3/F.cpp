// https://codeforces.com/contest/2008/problem/F

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int binpow(int a, int b, int mod) {
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
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n);

        vector<int> suffixSum(n + 1, 0);
        for (int i=0; i<n; i++) {
            cin >> arr[i];
        }

        for (int i=n-1; i>=0; i--) {
            suffixSum[i] = suffixSum[i + 1] + arr[i]; 
        }

        int upp = 0LL;
        for (int i=0; i<n-1; i++) {
            upp += ((arr[i] % MOD) * (suffixSum[i + 1] % MOD)) % MOD;
            upp %= MOD;
        }

        int bel = (((n * (n - 1)) % MOD) * binpow(2, MOD - 2, MOD)) % MOD;
        int ans = (upp * binpow(bel, MOD - 2, MOD)) % MOD;

        cout << ans << '\n';
    }

    return 0;
}