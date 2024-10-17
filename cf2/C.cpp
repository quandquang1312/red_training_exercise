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

vector<int> A, L, R, dp, height;
int n, v;

int RangeSum(int k) {
    return (k * (k + 1)) / 2;
}

int smFrom1(int l, int r) {
    int sm = 0;
    for (int i=l; i<r; i++) sm += RangeSum(i);

    return sm;
}
int max_height = 0;

int dfs(int u, int sd, int pl, int pr) {
    if (u == 0) return 0;
    if (pl > pr) return 0;
    if (pl <= 0 || pr <= 0) return 0;
    if (pr > v || pr > v) return 0;
    if (pl < height[u]) return 0;
    if (pr > height[u]) return 0;

    if (u == 1) { // root
        // LOG()
        int l = height[u] + 1, r = (v - height[u]);
        // LOG(v, height[u], l, r);
        if (A[u] == 0) {
            if (l > r) return 0;
            dp[u] = r - l + 1;
            dfs(L[u], 0, l, r); // left
            dfs(R[u], 1, l, r); // right
        } else {
            dp[u] = 1;
            dfs(L[u], 0, A[u], A[u]); // left
            dfs(R[u], 1, A[u], A[u]); // right
        }
    } else {
        if (sd == 0) {
            if (A[u] == 0) {
                dp[u] = smFrom1(pl, pr);
                dfs(L[u], 0, height[u], max(pr - 1); // left
                dfs(R[u], 1, 1, min(v - height[u], (pr - 1))); // right
            } else {
                dp[u] = 1;
                dfs(L[u], 0, A[u], A[u]); // left
                dfs(R[u], 1, A[u], A[u]); // right
            }
        } else {
            if (A[u] == 0) {
                dp[u] = smFrom1(pl, pr);
                dfs(L[u], 0, pr, v); // left
                dfs(R[u], 1, pr, v); // right
            } else {
                dp[u] = 1;
                dfs(L[u], 0, A[u], A[u]); // left
                dfs(R[u], 1, A[u], A[u]); // right
            }
        }
    }

    return dp[u];
}


int getHeight(int u) {
    if (u == 0) return 0;
    int ans = 1;
    int height_left  = getHeight(L[u]);
    int height_right = getHeight(R[u]);

    height[u] = ans + max(height_left, height_right);
    max_height = max(max_height, height[u]);

    return height[u];
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
        cin >> n >> v;

        A.assign(n + 1, 0);
        L.assign(n + 1, 0);
        R.assign(n + 1, 0);
        dp.assign(n + 1, 0);
        height.assign(n + 1, 0);
       
        for (int i=1; i<=n; i++) cin >> A[i];

        for (int i=1; i<=n; i++) cin >> L[i];
        for (int i=1; i<=n; i++) cin >> R[i];

        getHeight(1);


        for (int i=1; i<=n; i++) {
            height[i] -= 1;
            LOG(height[i]);
        }

        dfs(1, 0, 1, 1);
        // LOG(height);
        for (int i=1; i<=n; i++) {
            LOG(i, dp[i]);
        }
    }

    return 0;
}