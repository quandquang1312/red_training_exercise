#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    char grid[n+1][n+1];

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> grid[i][j];
        }
    }

    int max_col = -1, max_row = -1;
    for (int i=0; i<n; i++) {
        int tmp = 0, cnt = 1;
        for (int j=1; j<n; j++) {
            if ((grid[i][j] != grid[i][j-1])) {
                if (grid[i][j-1] == '#') {
                    tmp += binpow(cnt,cnt) % MOD;
                    tmp %= MOD;
                }
                cnt = 1;
            } else {
                cnt++;
            }
        }
        max_row = max(max_row, tmp);
        if (grid[i][n-1] != '#') continue;
        tmp += binpow(cnt,cnt) % MOD;
        tmp %= MOD;
        if (tmp > max_row) {
            max_row = max(max_row, tmp);
        }
    }

    for (int j=0; j<n; j++) {
        int tmp = 0, cnt = 1;
        for (int i=1; i<n; i++) {
            if (grid[i][j] != grid[i-1][j]) {
                if (grid[i-1][j] == '#') {
                    // cout << j << ": " << cnt << "-" << binpow(cnt,cnt) << endl;
                    tmp += binpow(cnt,cnt) % MOD;
                    tmp %= MOD;

                    // cout << j << ": " << tmp << endl;
                }
                cnt = 1;
            } else {
                cnt++;
            }
        }
        // cout << j << ": " << cnt << endl;
        max_col = max(max_col, tmp);
        if (grid[n-1][j] != '#') continue;
        tmp += binpow(cnt,cnt) % MOD;
        tmp %= MOD;
        if (tmp > max_col) {
            max_col = max(max_col, tmp);
        }
    }

    cout << max_row << " " << max_col << endl;

    return 0;
}