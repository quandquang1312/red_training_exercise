// https://codeforces.com/contest/1279/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e6 + 5; 
const int MOD  = 998244353;

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }

    return res % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<vector<int>> arr(n+1);

    int cnt[MAXN] {};
    for (int i=1; i<=n; i++) {
        int k; cin >> k;
        arr[i].assign(k,0);
        for (int j=0; j<k; j++) {
            cin >> arr[i][j];
            cnt[arr[i][j]]++;
        }
    }

    int rs = 0;
    for (int x=1; x<=n; x++) {
        for (auto &y : arr[x]) {
            // tmp1 = cnt[y] / n: probability that toy y is choosen
            int tmp1 = (cnt[y] * binpow(n, MOD - 2)) % MOD;
            // tmp2 = (1/n) * (1/arr[x].size()): probability that the student x is choosen among all n students
            int tmp2 = ((1LL * binpow(n, MOD - 2)) * (1LL * binpow(arr[x].size(), MOD - 2))) % MOD;
            rs += (tmp1 * tmp2) % MOD;
            rs %= MOD;
        }
    }

    cout << rs << endl;

    return 0;
}