// https://vjudge.net/problem/UVA-10721

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 55

int dp[MAXN][2][MAXN][MAXN];
int n, k, m;
vector<vector<int>> ret;

int solve(int idx, int prev, int num_seg, int continous_cnt) {
    if (continous_cnt > m) return 0;
    if (num_seg > k) return 0;

    if (idx > n) {
        if (num_seg < k) return 0;
        return 1;
    }

    if (dp[idx][prev][num_seg][continous_cnt] != -1) return dp[idx][prev][num_seg][continous_cnt];

    if (prev == 1) {
        int add1 = solve(idx+1, 1, num_seg, continous_cnt+1);
        int add0 = solve(idx+1, 0, num_seg+1, 1);

        return dp[idx][prev][num_seg][continous_cnt] = add1 + add0;
    } else { // prev == 0
        int add1 = solve(idx+1, 0, num_seg, continous_cnt+1);
        int add0 = solve(idx+1, 1, num_seg+1, 1);

        return dp[idx][prev][num_seg][continous_cnt] = add1 + add0;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);

    while ((cin >> n >> k >> m)) {
        memset(dp, -1, sizeof dp);
        int ans = solve(2, 0, 1, 1);
        cout << ans << endl;
    }

    return 0;
}