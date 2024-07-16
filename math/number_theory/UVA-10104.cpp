// https://vjudge.net/problem/UVA-10104

#include <bits/stdc++.h>
using namespace std;

#define int long long

// Extended Euclid
// AX * BY = D
// Extended Euclid to find X Y and D with a given pair A B
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

    int a, b;
    while (cin >> a >> b)
    {
        int x, y;
        int d = extended_euclid(a, b, x, y);
        cout << x << " " << y << " " << d << "\n";
    }

    return 0;
}