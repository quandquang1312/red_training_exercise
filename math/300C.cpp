// https://codeforces.com/problemset/problem/300/C
 
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
 
    int a, b, n;
    cin >> a >> b >> n;
 
    int total_exec = 0;
 
    auto checkGood = [](int a, int b, int numb) -> bool {
        while (numb) {
            if ((numb % 10 != a && numb % 10 != b))
                return false;
            numb /= 10;
        }
 
        return true;
    };
 
    int factorials[n+1] {};
    factorials[0] = 1;
    factorials[1] = 1;
 
    for (int i=2; i<=n; i++) factorials[i] = (factorials[i-1] * i) % mod;
 
    for (int numbA=0; numbA<=n; numbA++) {
        int numbB = n - numbA;
 
        int sm = numbA * a + numbB * b;
        if (checkGood(a, b, sm)) {
            int upper = factorials[n];
            int lower = (factorials[numbA] * factorials[numbB]) % mod;
            total_exec += (upper * binpow(lower, mod - 2)) % mod;
            total_exec %= mod;
        }
    }
 
    cout << total_exec << endl;
 
 
    return 0;
}