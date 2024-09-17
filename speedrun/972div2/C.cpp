#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
const int MAXN = 1e3 + 10;
#define INF 1e9
 
int n, m, dp[MAXN][5];
vector<string> str;
const string narek = "narek";
 
int nxt(int lst) {
    return (lst + 1) % 5;
}
 
int convert(char ch) {
    return (narek.find(ch));
}
 
int solve(int idx, int lst) {
    if (idx >= n) {
        if (lst == 4) return 0;
        return -(lst + 1);
    }
 
    if (dp[idx][lst] != -INF) {
        return dp[idx][lst];
    }
 
    int original_lst = lst;
 
    // not choose
    int nc = solve(idx + 1, original_lst);
 
    // choose
    int score = 0;
    for (int i=0; i<m; i++) {
        int j = convert(str[idx][i]);
        if (j == -1) continue;
        if (j == nxt(lst)) {
            lst = nxt(lst);
            if (j == 4) score += 5;
        } else {
            score--;
        }
    }
 
    int ch = score + solve(idx + 1, lst);
    return dp[idx][original_lst] = max(nc, ch);
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
        cin >> n >> m;
 
        str.assign(n, "");
        for (int i=0; i<n; i++) {
            for (int j=0; j<5; j++) dp[i][j] = -INF;
        }
 
        for (int i=0; i<n; i++) cin >> str[i];
 
        int ans = solve(0, 4);
        cout << ans << '\n';
    }
 
    return 0;
}