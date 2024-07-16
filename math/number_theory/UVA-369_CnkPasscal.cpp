// https://vjudge.net/problem/UVA-369
#include <bits/stdc++.h>
using namespace std;

#define int long long
int pascalVal[105][105];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    pascalVal[0][0] = 1;
    pascalVal[1][0] = 1, pascalVal[1][1] = 1;

    for (int i=2; i<=104; i++) {
        pascalVal[i][1] = 1;
        pascalVal[i][0] = 1;
        for (int j=2; j<=i; j++) {
            pascalVal[i][j] = pascalVal[i-1][j-1] + pascalVal[i-1][j];
        }
    }

    int n, m;
    while (cin >> n >> m) {
        if (n + m == 0) break;

        printf("%lld things taken %lld at a time is %lld exactly.\n",
            n, m, pascalVal[n+1][m+1]);
    }

    return 0;
}