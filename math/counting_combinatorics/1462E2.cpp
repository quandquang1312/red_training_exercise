// https://codeforces.com/contest/1462/problem/E2

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;
int f[200010];

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int inv(int n) {
    return binpow(n, MOD - 2LL);
}

void precalF() {
    f[0] = f[1] = 1;
    for (int i=2; i<200010; i++) f[i] = (f[i - 1] * i) % MOD;
}

int CnK(int n, int k) {
    if (n == k) return 1LL;
    if (n < k) return 0LL;

    return ((f[n] * inv(f[k]) % MOD) * (inv(f[n-k])) % MOD) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    precalF();

    int tc; cin >> tc;
    while (tc--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];

        sort(arr.begin(), arr.end());

        int ans = 0;
        for (int l=0; l<n; l++) {
            int r = upper_bound(arr.begin() + l, arr.end(), arr[l] + k) - arr.begin() - 1;
            if (arr[r] - arr[l] > k) continue;
            if (r - l < (m - 1)) continue;

            // cout << l << "-" << r << '\n';
            // choose arr[l] to avoid repeating and m - 1 elements in [l + 1, r]
            ans += CnK(r - l, m - 1);
            ans %= MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}