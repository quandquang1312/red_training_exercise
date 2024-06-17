// https://vjudge.net/problem/uva-11327

#include <bits/stdc++.h>
using namespace std;

#define int long long

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

    phi[1] += 1;

    vector<int> prefix(n+1, 0);
    for (int i=1; i<=n; i++) {
        prefix[i] += prefix[i-1] + phi[i];
    }
 
    return prefix;
}

int cooprime_kth(int n, int k)
{
    if (n == 1) {
        if (k == 1) return 0;
        else return 1;
    }

    int idx = 0;
    for (int i=1; i<=n; i++) {
        if (__gcd(i, n) == 1) {
            idx++;
            if (idx == k) return i;
        }
    }

    return 0;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    vector<int> prefix = euler_1_n(200010);

    int n;
    while ((cin >> n), n) {
        int pos = lower_bound(prefix.begin(), prefix.end(), n) - prefix.begin();
        int kth = n - prefix[pos-1];

        cout << cooprime_kth(pos, kth) << "/" << pos << endl;
    }

    return 0;
}