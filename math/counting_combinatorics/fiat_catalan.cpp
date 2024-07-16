// https://open.kattis.com/problems/fiat

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD  = 1e9 + 7;
const int MAXN = 1e5 + 5; 

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    int cat[MAXN];
    cat[1] = 1;
    for (int i=1; i<MAXN-1; i++) {
        int u = (((4 * i + 2) % MOD) * (cat[i] % MOD)) % MOD; 
        int inv = binpow(i+2, MOD - 2);
        cat[i+1] = (u * inv) % MOD;
    }

    cout << cat[n] << endl;


    return 0;
}