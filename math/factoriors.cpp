// https://open.kattis.com/problems/factovisors

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> primes;

void linear_sieve(int n = 50010)
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    linear_sieve();

    int n, m;
    while (cin >> n && cin >> m) {
        if (m == 0) {
            printf("%lld does not divide %lld!\n", m, n);
            continue;
        }

        int tmp_m = m;

        bool rs = true;
        for (int d=0; primes[d]*primes[d]<=m && d<primes.size(); d++) {
            int i = primes[d];

            if (m % i) continue;

            int cnt = 0;
            while (tmp_m % i == 0) {
                cnt++;
                tmp_m /= i;
            }

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
            if (n < tmp_m) rs = false;
        }

        if (rs) printf("%lld divides %lld!\n", m, n);
        else printf("%lld does not divide %lld!\n", m, n);
    }

    return 0;
}