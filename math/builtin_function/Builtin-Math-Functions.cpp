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

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a);
        a = a * a;
        b >>= 1;
    }

    return res;
}

// Legendre's Formula
int legendre(int n, int p)
{
    int ans = 0, k = 1;
    int pk = binpow(p, k);
    while (pk < n) {
        ans += n/pk;
        k++; 
        pk = binpow(p,k);
    }

    return ans;
}

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

// Modular Inverse using Extended Eulid when MOD is not prime
int inv(int n) {
    int x, y;
    extended_euclid(n, MOD, x, y);
    return (x % MOD + MOD) % MOD;
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