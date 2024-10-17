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

int numDiv(int n) {
    int ans = 1;
    for (int i=0; i<primes.size() && primes[i]*primes[i]<=n; i++) {
        int ai = 0;
        while (n % primes[i] == 0) ai++, n /= primes[i];
        ans *= (ai + 1);
    }
    
    if (n > 1) ans *= 2;
    return ans;
}

int sumDiv(int N) {
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
    vector<int> numDivs(200000 + 1, -1), sumDivs(200000 + 1, -1);
    map<int, set<int>> mp;
    
    while (tc--) {
        int n, m; cin >> n >> m;

        for (int i=1; i<=n; i++) {
            if (numDivs[i] == -1) numDivs[i] = numDiv(i);
            mp[numDivs[i]].insert(i);
        }

        for (int i=0; i<m; i++) {
            int x, a, b, c; cin >> x >> a >> b >> c;

            int dx = numDivs[x];
            if (sumDivs[x] == -1) sumDivs[x] = sumDiv(x);
            int sx = sumDivs[x];
            int ans = 0;

            for (int dy=max(0LL, dx - b); dy<=min(n, dx + b); dy++) {
                if (mp.find(dy) != mp.end()) {
                    for (auto &y : mp[dy]) {
                        if (y > n) continue;
                        if (abs(x - y) > a) continue;
                        if (sumDivs[y] == -1) sumDivs[y] = sumDiv(y);
                        int sy = sumDivs[y];
                        if (abs(sx - sy) <= c) ans++;
                    }
                }
            }

            cout << ans << " ";
        }

        cout << "\n";
    }

    return 0;
}