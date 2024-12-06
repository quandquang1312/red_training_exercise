// https://codeforces.com/contest/1061/problem/C

#include <bits/stdc++.h>
using namespace std;

const int MAXVAL = 1e6+ 10;
const long long MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    int mp[MAXVAL] {};
    int ans = 0;
    for (int i=0, x; i<n; i++) {
        cin >> x;
        map<int, int> red;
        for (int j=2; j*j<=x; j++) {
            if (x % j == 0) {
                if (mp[j] != 0) {
                    int f = mp[j];
                    ans = (ans + f) % MOD;
                    red[j + 1] += f;
                    red[j + 1] %= MOD;
                }

                int e = x / j;
                if (mp[e] != 0 && (e != j && mp[j] != 0)) {
                    int f = mp[e];
                    ans = (ans + f) % MOD;
                    red[e + 1] += f;
                    red[e + 1] %= MOD;
                }
            }
        }

        if (mp[x] != 0) {
            int f = mp[x];
            ans = (ans + f) % MOD;
            red[x + 1] += f;
            red[x + 1] %= MOD;
        }
        
        for (auto &[e, f] : red) {
            mp[e] = (mp[e] + f) % MOD;
        }

        // the only element of the subsequence
        ans = (ans + 1) % MOD;
 
        // the first element of the subsequences
        mp[2] = (mp[2] + 1) % MOD;
    }

    cout << ans << "\n";

    return 0;
}