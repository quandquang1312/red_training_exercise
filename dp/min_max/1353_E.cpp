// https://codeforces.com/contest/1353/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

int n, k;
string str;
vector<int> prefix;

vector<vector<int>> dp;

int solve(int idx, int exist1s) {
    if (idx > n) return 0;

    if (dp[idx][exist1s] != -1) return dp[idx][exist1s];

    // str[idx] set to 1 (or already is)
    int new_idx = min(n, idx + k - 1);
    int val_to_change = prefix[new_idx] - prefix[idx];
    int change_1 = (str[idx] != '1') + val_to_change + solve(idx + k, 1);

    // str[idx] set to 0 (or already is)
    // set all from idx to n to be 0s
    val_to_change = prefix[n] - prefix[idx - 1];
    int change_0 = (str[idx] != '0') + val_to_change;
    if (!exist1s) {
        // able to set idx to 0s
        change_0 = min(change_0, (str[idx] != '0') + solve(idx + 1, exist1s));
    }

    return dp[idx][exist1s] = min(change_1, change_0);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> k;
        cin >> str;

        prefix.assign(n + 1, 0);
        dp.assign(n + 1, vector<int>(2, -1));

        for (int i=0; i<n; i++)
            prefix[i + 1] = prefix[i] + (str[i] == '1');
        str = '_' + str;

        int ans = solve(1, 0);

        cout << ans << "\n";
    }

    return 0;
}