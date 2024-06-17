// https://www.spoj.com/problems/ETF/

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e6+2;

vector<int> euler_1_n(int n)
{
    vector<int> phi(n+1);
    for (int i=0; i<=n; i++) phi[i] = i;

    for (int i=2; i<=n; i++) {
        if (phi[i] == i) {
            for (int j=i; j<=n; j+=i) phi[j] -= phi[j] / i;
        }
    }

    return phi;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    vector<int> phi = euler_1_n(MAXN);

    while (tc--)
    {
        int n; cin >> n;
        cout << phi[n] << endl;
    }

    return 0;
}