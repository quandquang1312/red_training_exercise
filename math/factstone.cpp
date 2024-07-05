// https://open.kattis.com/problems/factstone?tab=metadata

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

    int year = 1960;
    while (cin >> year) {
        if (year == 0) break;

        int d = ((year - 1960)/10 + 2);

        double maxx = pow(2,d);

        int n = 1;
        double sumlogn = 0;
        while (sumlogn < maxx) {
            sumlogn += log2(n);
            n++;
        }

        cout << n - 2 << endl;
        year += 10;
    }

    return 0;
}