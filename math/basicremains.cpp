// https://open.kattis.com/problems/basicremains

#include <bits/stdc++.h>
using namespace std;

#define int long long

int binpow(int a, int b, int mod) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }

    return res;
}

int convertbaseTo10(string number, int base)
{ 
    int ans = 0;
    for (int i=number.size() - 1; i>=0; i--) {
        int temp = (number[i] - '0');
        ans += temp * pow(base, number.size() - i - 1);
    }

    return ans;
}

int solveIn10(string number, int base, int m)
{
    int ans = 0;
    for (int i=0; i<number.size(); i++) {
        int temp = (number[i] - '0') * binpow(base, number.size() - i - 1, m);
        ans = (ans + temp) % m;
        ans %= m;
    }

    return ans;
}

int convert10ToBase(int number, int base) {
    int ans = 0, p = 0;
    while (number) {
        ans = (number % base) * pow(10, p++) + ans;
        number /= base;
    }
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    while (true) {
        int b, m;
        string p;
        cin >> b;
        if (b == 0) break;
        cin.ignore();
        cin >> p;
        cin >> m;

        int new_m = convertbaseTo10(to_string(m), b);
        int n10 = solveIn10(p, b, new_m);
        int ans = convert10ToBase(n10, b);
        cout << ans << endl;
    }

    return 0;
}