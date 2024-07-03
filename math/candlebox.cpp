// https://open.kattis.com/problems/candlebox

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int d, r, t;
    cin >> d >> r >> t;

    int age = -1, presum[100] {};
    presum[3] = 0;

    for (int i=4; i<=99; i++) {
        presum[i] += presum[i-1] + i;
    }

    for (int age = 4; age<=99; age++) {
        int rightR = presum[age];
        int rightT = presum[age-d] + 3;

        // if (age == 7) cout << age << "-" << rightR + rightT << "-" << r + t << endl;
        if (rightR + rightT == t + r) {
            cout << r - rightR << endl;
            return 0;
        }
    }

    return 0;
}