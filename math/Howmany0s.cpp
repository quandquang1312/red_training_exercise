#include <bits/stdc++.h>
using namespace std;

#define int unsigned long long

int count(int32_t n) {
    int ret = 0, n10 = 1, ntail = 0;
    while (n) {
        if (n%10) {
            ret += n/10*n10;
        } else {
            ret += 
        }
    }
}

int32_t main() {
    int32_t m, n;
    while ((cin >> m >> n), (m != -1)) {
        cout << countZeros(n) - countZeros(m-1) << endl;
    }
    return 0;
}