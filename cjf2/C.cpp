#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 444'449;

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int CnK(int n, int k) {
    if (k > n) return 0LL;
    if (k == n) return 1LL;

    k = min(k, n - k);

    int numerator = 1, denominator = 1;
    for (int i=0; i<k; i++) {
        numerator = (numerator * (n - i) % MOD) % MOD;
        denominator = (denominator * (i + 1) % MOD) % MOD;
    }

    int denominator_inv = binpow(denominator, MOD - 2);
    return (numerator * denominator_inv) % MOD;
}

vector<int> odr;

void dfs(int u, vector<int>& L, vector<int>& R) {
    if (L[u] != -1) dfs(L[u], L, R);
    odr.push_back(u);
    if (R[u] != -1) dfs(R[u], L, R);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, v; cin >> n >> v;

        vector<int> A(n), L(n), R(n);

        odr.clear();

        for (int i=0; i<n; i++) cin >> A[i];
        for (int i=0; i<n; i++) cin >> L[i], L[i]--;
        for (int i=0; i<n; i++) cin >> R[i], R[i]--;

        int rt = 0;
        vector<int> anc(n, -1);
        for (int i=0; i<n; i++) {
            if (L[i] != -1) anc[L[i]] = i;
            if (R[i] != -1) anc[R[i]] = i; 
        }

        for (int i=0; i<n; i++) {
            if (anc[i] == -1) rt = i;
        }

        dfs(rt, L, R);

        vector<pair<int, int>> fixed;

        fixed.push_back({0, -1});
        for (int i=0; i<n; i++) {
            int pos = A[odr[i]];
            if (pos != 0) fixed.push_back({pos, i});
        }
        fixed.push_back({v + 1, n});

        int ans = 1LL;
        for (int i=1; i<fixed.size(); i++) {
            auto [pos1, odr1] = fixed[i];
            auto [pos2, odr2] = fixed[i-1];
            
            ans = (ans * CnK((pos1 - pos2 - 1) % MOD, (odr1 - odr2 - 1) % MOD)) % MOD; 
        }

        cout << ans << "\n";
    }

    return 0;
}