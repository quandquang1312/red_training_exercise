#include <bits/stdc++.h>
using namespace std;

#define int long long

// Calculate phi(n) in O(sqrt(n))
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

// Euler totient from 1 to n in O(n log(log(n)))
vector<int> euler_1_n(int n)
{
    vector<int> phi(n+1);
    for (int i=0; i<=n; i++) phi[i] = i;

    for (int i=2; i<=n; i++) {
        if (phi[i] == i) {
            for (int j=i; j<=n; j+=i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    return phi;
}

int32_t main() {


    return 0;
}