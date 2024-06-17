#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e4;

// Sieve of Eratosthenes O(n log n)
void eratos_seive(int n)
{
    vector<int> primes;
    bool is_composite[MAXN] {};

    for (int i=2; i<n; i++) {
        if (!is_composite[i]) primes.push_back(i);
        for (int j=2; i*j<n; j++) is_composite[i*j] = true;
    }
}

// Linear sieve O(n)
void linear_sieve(int n)
{
    vector<int> primes;
    bool is_composite[MAXN] {};

    for (int i=2; i<n; i++) {
        if (!is_composite[i]) primes.push_back(i);
        for (int j=0; j<primes.size() && i * primes[j] < n; j++) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// Linear sieve on euler totient O(n)
void sieve(int n)
{
    vector<int> primes;
    bool is_composite[MAXN] {};
    int phi[MAXN];

    phi[1] = 1;
    for (int i=2; i<n; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }

        for (int j=0; j<primes.size() && i * primes[j] < n; j++) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j]) {
                phi[i * primes[j]] = primes[j] * phi[i]; // primes[j] devides i
                break;
            } else {
                phi[i * primes[j]] = phi[i] * phi[primes[j]]; // primes[j] does not devide i
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    return 0;
}