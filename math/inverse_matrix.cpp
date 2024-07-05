// https://open.kattis.com/problems/matrix

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

    int a, b, c, d, t = 1;
    while (cin >> a >> b >> c >> d)
    {
        int prefix = 1 / (a*d - b*c);
        int a1 = d * prefix;
        int b1 = -b * prefix;
        int c1 = -c * prefix;
        int d1 = a * prefix;
        cout << "Case " << t++ << ":\n";
        cout << a1 << " " << b1 << "\n" << c1 << " " << d1 << endl;
    }

    return 0;
}