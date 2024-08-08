// https://codejam.lge.com/problem/25334

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e6 + 5;
const int mod = 1e9 + 7;

int factorial[MAXN];

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

int inv(int n) {
    return binpow(n, mod - 2);
}

int CnK(int n, int k) {
    if (n == k) return 1;
    if (n < k) return 0;

    return ((factorial[n] * inv(factorial[k]) % mod) * (inv(factorial[n-k])) % mod) % mod;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;

    factorial[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        factorial[i] = factorial[i - 1] * i % mod;
    }

    while (tc--) {
        int n, k, d;
        cin >> n >> k;
        string str; cin >> str;

        vector<int> z;
        int cnt = 0;
        for (int i=0; i<n; i++) {
            if (str[i] == '1') cnt++;
        }

        if (cnt % k != 0) {
            cout << "0\n";
        } else if (cnt == 0) {
            int ans = CnK(n-1, k-1);
            cout << ans << "\n";
        } else if (k == 1) {
            cout << "1\n";
        } else {
            d = cnt / k;
            int idx_1 = 0;
            if (d == 1) {
                for (int i=0; i<n; i++) {
                    if (str[i] == '0') continue;
                    idx_1++;
                    z.push_back(i);
                }

                int ans = 1;
                if (z.size() == 1) {
                    cout << "1\n";
                    continue;
                }

                for (int i=0; i<z.size() - 1; i++) {
                    int len = z[i + 1] - z[i] - 1;
                    if (len) {
                        ans *= (len + 1) % mod; 
                        ans %= mod;
                    }
                }

                cout << ans << endl;
            } else {
                for (int i=0; i<n; i++) {
                    if (str[i] == '0') continue;
                    idx_1++;
                    if (idx_1 % d == 0 && idx_1 != cnt) {
                        z.push_back(i);
                    } else if (idx_1 % d == 1 && idx_1 != 1) {
                        z.push_back(i);
                    }
                }

                int ans = 1;
                for (int i=0; i<z.size() - 1; i+=2) {
                    int len = z[i + 1] - z[i] - 1;
                    if (len) {
                        ans *= (len + 1) % mod; 
                        ans %= mod;
                    }
                }

                cout << ans << endl;
            }
        }
    }

    return 0;
}