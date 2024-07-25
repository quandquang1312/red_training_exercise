// https://vjudge.net/problem/UVA-10090

#include <bits/stdc++.h>
using namespace std;

#define int long long

int extended_euclid(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1)  = make_tuple(x1, x - q * x1);
        tie(y, y1)  = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }

    return a1;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n = -1;
    while (cin >> n) {
        if (n == 0) break;
        int c1, n1, c2, n2;
        cin >> c1 >> n1;
        cin >> c2 >> n2;

        int x0, y0;
        int d = extended_euclid(n1, n2, x0, y0);
        if (n % d != 0) {
            cout << "failed\n";
            continue;
        }

        int low = abs((x0 * n) / (n2 / d)) + 1;
        int upp = abs((y0 * n) / (n1 / d));

        if (low > upp) {
            cout << "failed\n";
            continue;
        }

        int x1 = (x0 * n) + (n2 / d) * low;
        int y1 = (y0 * n) - (n1 / d) * low;
        int x2 = (x0 * n) + (n2 / d) * upp;
        int y2 = (y0 * n) - (n1 / d) * upp;
        if (x1 * c1 + y1 * c2 > x2 * c1 + y2 * c2) {
            cout << x2 << " " << y2 << endl;
        } else cout << x1 << " " << y1 << endl;
    }

    return 0;
}