// https://vjudge.net/problem/UVA-10929

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    string n;
    while (cin >> n) {
        if (n.compare("0") == 0) break;

        int sm_odd = 0, sm_even = 0;
        for (int i=1; i<=n.size(); i++) {
            if (i & 1) sm_odd += n[i-1] - '0';
            else sm_even += n[i-1] - '0';
        }

        if ((sm_odd - sm_even) % 11 == 0) {
            printf("%s is a multiple of 11.\n", n.c_str());
        } else {
            printf("%s is not a multiple of 11.\n", n.c_str());
        }
    }

    return 0;
}