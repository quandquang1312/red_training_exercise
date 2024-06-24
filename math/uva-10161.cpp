// https://vjudge.net/problem/UVA-10161

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

    int n = 1;
    while ((cin >> n), n) {
        int i = 1;
        int x = sqrt(n);

        if (x * x != n) x += 1;

        int center = ((x*x) + (x-1)*(x-1) + 1) / 2;
        // cout << n << ": " << center << endl;
        if (n == center) {
            cout << x << " " << x << endl; 
        } else {
            if (x % 2 == 0) {
                if (n > center) cout << x << " " << (x*x - n + 1) << "\n"; //  << x << endl;
                else cout << n - ((x-1)*(x-1)) << " " << x << "\n"; //<< center - n + 1 << endl; 
            } else {
                if (n > center) cout << (x*x - n + 1) << " " << x << "\n"; // << (x*x - n + 1) << endl;
                else cout << x << " " << n - ((x-1)*(x-1) + 1) + 1 << "\n"; // << x << endl;
            }
        }

        // cout << n << ": " << x << endl;
    }

    return 0;
}