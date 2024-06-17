// https://codeforces.com/problemset/problem/546/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 5e6 + 5;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    vector<int> pfactors(MAXN);
    bool isPrime[MAXN];

    memset(isPrime, true, sizeof isPrime);
    pfactors[1] = 1;
    isPrime[1] = false;

    for (int i=2; i<MAXN; i++) {
        if (isPrime[i]) {
            for (int j=i; j<MAXN; j+=i) {
                int cur = j;
                while (cur % i == 0) {
                    pfactors[j]++;
                    cur /= i;
                }
                isPrime[j] = false;
            }
        }
    }

    for (int i=1; i<MAXN; i++) pfactors[i] += pfactors[i-1];

    int tc; cin >> tc;
    while (tc--)
    {
        int a, b; cin >> a >> b;

        int ans = pfactors[a] - pfactors[b];

        cout << ans << endl;
    }

    return 0;
}