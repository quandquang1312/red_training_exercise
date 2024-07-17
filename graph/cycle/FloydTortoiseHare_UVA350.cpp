// https://vjudge.net/problem/UVA-350

#include <bits/stdc++.h>
using namespace std;

#define int long long

int M, I, Z, L;

int f(int x) {
    return (Z * x + I) % M;
}

pair<int, int> floydCycleFinding(int x0) {
    int t = f(x0), h = f(f(x0));

    while (t != h) { t = f(t); h = f(f(h)); }
    int mu = 0; h = x0;
    while (t != h) { t = f(t); h = f(h); mu++; }
    int lamb = 1; h = f(t);
    while (t != h) { h = f(h); lamb++; }
    return {mu, lamb};
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc = 1;
    while (cin >> Z >> I >> M >> L)
    {
        if (Z + I + M + L == 0) break;
        auto [mu, lamb] = floydCycleFinding(L);
        cout << "Case " << tc++ << ": " << lamb << endl;
    }


    return 0;
}