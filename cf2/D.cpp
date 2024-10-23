#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200010

const int INF = 1e13;
const int MOD = 1e9 + 7;
const int THRESHOLD = 700;

vector<int> primes;

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

class MergeSortTree {
public:
    vector<vector<int>> tree;
    vector<int> ys;
    int n;

    MergeSortTree() {}

    MergeSortTree(const vector<int>& arr, const vector<int>& y) {
        ys = y;
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    MergeSortTree& operator=(const MergeSortTree& other) {
        if (this != &other) {
            this->n = other.n;
            this->ys = other.ys;
            this->tree = other.tree;
        }
        return *this;
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = vector<int>(1, arr[start]);
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;
            build(arr, leftChild, start, mid);
            build(arr, rightChild, mid + 1, end);

            merge(tree[leftChild].begin(), tree[leftChild].end(),
                  tree[rightChild].begin(), tree[rightChild].end(),
                  back_inserter(tree[node]));
        }
    }

    pair<int, int> getIndex(int lo, int hi) {
        int fi = lower_bound(ys.begin(), ys.end(), lo) - ys.begin();
        int se = upper_bound(ys.begin(), ys.end(), hi) - 1 - ys.begin();
        if (fi == n) return {-1, -1};
        return {fi, se};
    }

    int query(int node, int start, int end, int l, int r, int d, int k) {
        if (start > r || end < l) {
            return 0;
        }
        if (start >= l && end <= r) {
            int countD = lower_bound(tree[node].begin(), tree[node].end(), d) - tree[node].begin();
            int countK = upper_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
            return max(0LL, countK - countD);
        }

        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;
        int leftResult = query(leftChild, start, mid, l, r, d, k);
        int rightResult = query(rightChild, mid + 1, end, l, r, d, k);
        return leftResult + rightResult;
    }

    int query(int l, int r, int d, int k) {
        return query(0, 0, n - 1, l, r, d, k);
    }
};

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

    linear_sieve(MAXN + 10);
    vector<int> numDivs(MAXN, -1), sumDivs(MAXN, -1);
    map<int, pair<vector<int>, vector<int>>> mp;

    for (int i=1; i<MAXN; i++) {
        numDivs[i] = numDiv(i);
        sumDivs[i] = sumDiv(i);
        mp[numDivs[i]].first.push_back(sumDivs[i]);
        mp[numDivs[i]].second.push_back(i);
    }

    MergeSortTree vmst[160];

    for (int i=1; i<160; i++) {
        if (mp[i].first.size() <= THRESHOLD) continue;
        if (mp.count(i) == 0) continue;
        auto vct = mp[i];
        MergeSortTree stt(vct.first, vct.second);
        vmst[i] = stt;
    }

    while (tc--) {
        int n, m; cin >> n >> m;

        for (int i=0; i<m; i++) {
            int x, a, b, c; cin >> x >> a >> b >> c;

            int dx = numDivs[x];
            int sx = sumDivs[x];
            int ans = 0;

            for (int dy=max(0LL, dx - b); dy<=dx + b; dy++) {
                if (mp[dy].first.size() > THRESHOLD) {
                    auto [lo, hi] = vmst[dy].getIndex(max(0LL, x - a), min(n, x + a));
                    if (lo == -1) continue;
                    int cnt = vmst[dy].query(lo, hi, sx - c, sx + c);
                    ans += cnt;
                } else {
                    for (auto &y : mp[dy].second) {
                        if (y > n) break;
                        if (abs(x - y) > a) continue;
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