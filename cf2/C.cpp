#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll MOD = 444'449;
const int MAXN = 100010;

#define LOG(...) print_with_dash(#__VA_ARGS__, __VA_ARGS__)

template<typename T>
void print_with_dash(const std::string& names, T value) {
    std::cout << names << ": " << value << std::endl;
}

template<typename T, typename... Args>
void print_with_dash(const std::string& names, T value, Args... args) {
    size_t pos = names.find(',');
    std::cout << names.substr(0, pos) << ": " << value << " - ";
    print_with_dash(names.substr(pos + 1), args...);
}

int f[MAXN];

ll binpow(ll a, ll b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int inv(int n) {
    return binpow(n, MOD - 2LL);
}

void precalF() {
    f[0] = f[1] = 1;
    for (int i=2; i<MAXN; i++) f[i] = (f[i - 1] * i) % MOD;
}

int CnK(int n, int k) {
    if (n == k) return 1LL;
    if (n < k) return 0LL;

    return ((f[n] * inv(f[k]) % MOD) * (inv(f[n-k])) % MOD) % MOD;
}

vector<int> A, L, R, odr;
int n, v;

void dfs(int u) {
    if (L[u] != 0) dfs(L[u]);
    odr.push_back(u);
    if (R[u] != 0) dfs(R[u]);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    precalF();

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> v;

        A.assign(n + 1, 0);
        L.assign(n + 1, 0);
        R.assign(n + 1, 0);
        odr.clear();
       
        for (int i=1; i<=n; i++) cin >> A[i];
        for (int i=1; i<=n; i++) cin >> L[i];
        for (int i=1; i<=n; i++) cin >> R[i];

        dfs(1);

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
            
            ans = (ans * CnK(pos1 - pos2 - 1, odr1 - odr2 - 1)) % MOD; 
        }

        cout << ans << "\n";
    }

    return 0;
}