// https://vjudge.net/problem/UVA-10491

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    double cow, car, show;
    while (cin >> cow >> car >> show) {
        double ttl = cow + car;
        double cowcar = (cow / ttl) * (car / (ttl - show - 1));
        double carcar = (car / ttl) * ((car - 1) / (ttl - show - 1)); 

        double prob = cowcar + carcar;
        printf("%.5f\n", prob);
    }

    return 0;
}