// https://open.kattis.com/problems/collatz

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    while (cin >> n >> m) {
        if (n == 0) break;
        int original_n = n, original_m = m;

        unordered_map<int, int> mp1, mp2;
        int cnt1 = 0, cnt2 = 0;
        mp1[n] = cnt1++, mp2[m] = cnt2++;

        while (n != 1) {
            if (n & 1)
                n = n * 3 + 1;
            else n /= 2;

            mp1[n] = cnt1++; 
        }

        while (m != 1) {
            if (m & 1)
                m = m * 3 + 1;
            else m /= 2;

            mp2[m] = cnt2++; 
        }

        int step1 = -1, step2 = -1, kys = -1, mmin = 1e9;
        for (auto &[k, v] : mp1) {
            if (mp2.find(k) != mp1.end()) {
                if (mp2[k] < mmin || mp1[k] < mmin) {
                    step1 = mp1[k];
                    step2 = mp2[k];
                    kys   = k;
                    mmin  = min(step1, step2);
                }
            }
        }

        printf("%lld needs %lld steps, %lld needs %lld steps, they meet at %lld\n", original_n, step1, original_m, step2, kys);
    }

    return 0;
}
