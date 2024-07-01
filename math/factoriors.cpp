// https://open.kattis.com/problems/factovisors

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main()
{
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    while (cin >> n && cin >> m) {
        if (m % n == 0) {
            printf("%d divides %d!\n", m, n);
        } else {
            printf("%d does not divide %d!\n", m, n);
        }
    }

    return 0;
}