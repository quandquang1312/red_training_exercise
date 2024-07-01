// https://vjudge.net/problem/UVA-11718

#include <bits/stdc++.h>
using namespace std;

#define int long long

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
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++)
    {
        int n, k, mod;
        cin >> n >> k >> mod;

        int arr[n], sm = 0;
        for (int i=0; i<n; i++) {
            cin >> arr[i];
            sm += arr[i];
        }

        int npk = binpow(n, k-1, mod);
        int freq = ((npk % mod) * (k % mod)) % mod;
        int rs = (freq * (sm % mod)) % mod;

        cout << "Case " << t << ": " << rs << endl;
    }

    return 0;
}