// https://open.kattis.com/problems/factovisors

#include <bits/stdc++.h>
using namespace std;

vector<int> primes;

void linear_sieve(int n = 50000)
{
    vector<bool> isPrime(n+1, true);

    for (int i=2; i<n; i++) {
        if (isPrime[i]) primes.push_back(i);
        for (int j=0; j<primes.size() && i * primes[j] < n; j++) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

int32_t main()
{
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    linear_sieve();

    int n, m;
    while (cin >> n && cin >> m) {
        int tmp_m = m;

        // if (m < n) {
        //     printf("%d does not divide %d!\n", m, n);
        //     continue;
        // }

        bool rs = true;
        for (int d=0; primes[d]*primes[d]<=tmp_m && d<primes.size(); d++) {
            int i = primes[d];
            int cnt = 0;
            while (tmp_m % i == 0) {
                cnt++;
                tmp_m /= i;
            }

            if (cnt == 0) continue;

            int cnt2 = 0, pk = i;
            while (pk < n) {
                cnt2 += n/pk;
                pk *= i;
            }

            if (cnt > cnt2) {
                rs = false;
                break;
            }
        }

        if (tmp_m != 1) {
            if (tmp_m > n) rs = false;
        }

        if (rs) printf("%d divides %d!\n", m, n);
        else printf("%d does not divide %d!\n", m, n);
    }

    return 0;
}