// https://vjudge.net/problem/UVA-350

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

    int Z, I, M, L, tc = 1;
    while (cin >> Z >> I >> M >> L)
    {
        if (Z + I + M + L == 0) break;

        vector<bool> appear(10000, false);
        appear[L] = true;
        int original_L = L, cnt = 1;
        L = (Z * L + I) % M;

        while (appear[L] == false) {
            appear[L] = true;
            L = (Z * L + I) % M;
            cnt++;
        }

        if (L != original_L) cnt--;
        cout << "Case " << tc++ << ": " << cnt << endl;
    }



    return 0;
}