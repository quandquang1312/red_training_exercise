// https://codeforces.com/contest/1324/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 2005

int n, h, l, r;
int dp[MAXN][MAXN];

int normalize(int a) {
    return a % h;
}

int solve_topdown(int idx, int prev, const vector<int> &arr) {
    // NOTE: pop the first item (0) of the array first
    if (idx >= n) return 0;

    if (idx >= 0 && dp[idx][prev] != -1) return dp[idx][prev];

    int ans = (prev >= l && prev <= r);

    // choose a_next
    int a_next = solve_topdown(idx + 1, normalize(prev + (arr[idx + 1] - 1)), arr);

    // choose a_1_next
    int a_1_next = solve_topdown(idx + 1, normalize(prev + arr[idx + 1]), arr);

    if (idx >= 0) return dp[idx][prev] = ans + max(a_next, a_1_next);
    return max(a_next, a_1_next);
}

int solve_bottomup(const vector<int> &arr) {
    n += 1;
    int ans = 0;
    dp[0][0] = 0;

    for (int i=1; i<n; i++) {
        for (int j=0; j<h; j++) {
            int ans_j = (j >= l && j <= r);

            int prev_a   = ((j - arr[i]) % h + h) % h;
            int prev_a_1 = ((j - (arr[i] - 1)) % h + h) % h;

            if (dp[i-1][prev_a] != -1) {
                dp[i][j] = max(dp[i][j], ans_j + dp[i-1][prev_a]);
            }
            
            if (dp[i-1][prev_a_1] != -1) {
                dp[i][j] = max(dp[i][j], ans_j + dp[i-1][prev_a_1]);
            }
        }
    }

    for (int i=0; i<h; i++) {
        ans = max(ans, dp[n-1][i]);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    memset(dp, -1, sizeof(dp));

    cin >> n >> h >> l >> r;

    vector<int> arr(n + 1, 0);
    for (int i=1; i<=n; i++) cin >> arr[i];

    int ans = solve_bottomup(arr);
    cout << ans << "\n";

    return 0;
}