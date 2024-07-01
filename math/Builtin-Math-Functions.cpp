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

// Sieve of Eratosthenes
vector<int> sieveOfEratos(int n)
{
    vector<int> primes;
    vector<bool> isPrime(n+1, true);

    for (int i=2; i<=n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j=i*2; j<=n; j+=i) isPrime[j] = false;
        }
    }

    return primes;
}

// Linear sieve O(n)
void linear_sieve(int n)
{
    vector<int> primes;
    vector<bool> isPrime(n+1, true);

    for (int i=2; i<n; i++) {
        if (isPrime[i]) primes.push_back(i);
        for (int j=0; j<primes.size() && i * primes[j] < n; j++) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

// Generate prime factors
vector<int> primeFactor(int n, vector<int> primes) {
    vector<int> factors;

    for (int i=0; i<primes.size() && primes[i] * primes[i] <= n; i++) {
        while (n % primes[i] == 0) {
            factors.push_back(primes[i]);
            n /= primes[i];
        }
    }

    if (n != 1) factors.push_back(n);
    return factors;
}

int32_t main() {

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> pr = sieveOfEratos(n);

    for (auto &e : pr) {
        cout << e << " ";
    } cout << endl;

    return 0;
}