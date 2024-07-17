// https://vjudge.net/problem/UVA-10368

#include <bits/stdc++.h>
using namespace std;

#define int long long

int dp[1000][1000][2];
bool ans = false;

bool solve(int n, int m, int p, int ori) {
    // cout << n << "-" << m << "-" << p << endl;
    if (n < 0 || m < 0) return 0;
    if (n == 0 || m == 0) {
        // cout << (p == 0 ? "Stan\n" : "Ollie\n");
        if (p == ori) return true;
        return false;
    }

    if (n < m) {
        bool tmp = false;
        for (int i=1; i*n<=m; i++) {
            tmp |= solve(n, m-i*n, 1-p, p);
        }
        return tmp;
    } else {
        bool tmp = false;
        for (int i=1; i*m<=n; i++) {
            tmp |= solve(n-i*m, m, 1-p, p);
        }
        return tmp;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;
    ans = solve(n,m,0,0);
    if (ans) cout << "Stan wins\n";
    else cout << "Ollie wins\n";

    return 0;
}