// http://poj.org/problem?id=2635

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e5;
vector<int> primes;

// Linear sieve O(n)
void linear_sieve(int n)
{
    bool is_composite[MAXN] {};

    for (int i=2; i<n; i++) {
        if (!is_composite[i]) primes.push_back(i);
        for (int j=0; j<primes.size() && i * primes[j] < n; j++) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
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

    linear_sieve(MAXN-1);

    int k = 1, l = 1;
    while ((cin >> k >> l), (k && l)) {
        int minn = 1e9;
        for (int i=0; i<primes.size(); i++) {
            while (k % primes[i] == 0) {
                k /= primes[i];
                minn = min(minn, primes[i]);
            }
        }

        if (minn > l) cout << "GOOD\n";
        else cout << "BAD " << minn << endl;
    }

    return 0;
}