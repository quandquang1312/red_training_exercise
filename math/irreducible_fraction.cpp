// https://vjudge.net/problem/UVA-10179

#include <bits/stdc++.h>
using namespace std;

#define int long long

int phi_func(int n)
{
    int res = n;
    for (int i=2; i*i<=n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }

    if (n > 1) res -= res / n;
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n = -1;
    while ((cin >> n), n != 0)
    {
        int ans = phi_func(n);
        cout << ans << endl;
    }


    return 0;
}