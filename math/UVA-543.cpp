// https://vjudge.net/problem/UVA-543

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    bool isComp[MAXN+1] {};
    vector<int> primes;

    for (int i=2; i<=MAXN; i++) {
        if (!isComp[i]) primes.push_back(i);
        for (int j=0; j<primes.size() && i * primes[j] < MAXN; j++) {
            isComp[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }

    int n;
    while (cin >> n) {
        if (!n) break;

        bool found = false;
        for (int l=2; l<=n; l++) {
            if (!isComp[l] && !isComp[n-l]) {
                cout << n << " = " << l << " + " << n - l << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Goldbach's conjecture is wrong.\n";
        }
    }

    return 0;
}