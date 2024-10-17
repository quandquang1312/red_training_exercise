#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e13;
const int MOD = 1e9 + 7;

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

vector<int> primes;

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

void linear_sieve(int n)
{
    primes.clear();
    vector<bool> isPrime(n+1, true);

    for (int i=2; i<n; i++) {
        if (isPrime[i]) primes.push_back(i);
        for (int j=0; j<primes.size() && i * primes[j] < n; j++) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

int numDiv(int n, int upp) {
    int ans = 1;
    for (int i=0; i<primes.size() && primes[i]*primes[i]<=n; i++) {
        int ai = 0;
        while (n % primes[i] == 0) ai++, n /= primes[i];
        ans *= (ai + 1);
        if (upp != 0 && ans > upp) break;
    }
    
    if (n > 1) ans *= 2;
    return ans;
}

vector<int> sumDiv(int N) {
    vector<int> rs(N + 1);
    int ans = 1;
    for (int i = 0; (i < (int)primes.size()) && (primes[i] * primes[i] <= N); ++i)
    {
        int multiplier = primes[i], total = 1;
        while (N % primes[i] == 0)
        {
            N /= primes[i];
            total += multiplier;
            multiplier *= primes[i];
        }
        ans *= total;
    }
    if (N != 1)
        ans *= (N + 1);
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    linear_sieve(200001);

    unordered_map<int, set<int>> mp;
    unordered_map<int, int> dx, sx;

    while (tc--) {
        int n, m; cin >> n >> m;

        vector<tuple<int, int, int, int>> queries;
        set<int> xs;
        int min_dx = INF, max_dx = 0;
        for (int i=0; i<m; i++) {
            int x, a, b, c; cin >> x >> a >> b >> c;
            queries.push_back({x, a, b, c});
            if (dx.find(x) == dx.end()) dx[x] = numDiv(x, 0);
            mp[dx[x]].insert(x);
            min_dx = min(min_dx, dx[x]);
            max_dx = max(max_dx, dx[x]);
        }

        for (int i=1; i<=n; i++) {
            if (dx.find(i) == dx.end()) dx[i] = numDiv(i, max_dx + 5);
            mp[dx[i]].insert(i);
            if (dx[i] >= min_dx - 5 && dx[i] <= max_dx + 5) {
                sx[i] = sumDiv(i);
            }
        }

        for (int i=0; i<m; i++) {
            auto [x, a, b, c] = queries[i];

            int dx_ = dx[x];
            int sx_ = sx[x];
            int ans = 0;

            for (int dy=max(1LL, dx_ - b); dy<=min(n, dx_ + b); dy++) {
                if (mp.find(dy) != mp.end()) {
                    for (auto &y : mp[dy]) {
                        if (y > n) continue;
                        if (abs(x - y) > a) continue;
                        int sy = sx[y];
                        if (abs(sx_ - sy) <= c) ans++;
                    }
                }
            }

            cout << ans << " ";
        }

        cout << "\n";
    }

    return 0;
}