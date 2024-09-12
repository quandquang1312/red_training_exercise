// https://cses.fi/problemset/task/1750

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200010
const int LOG = 30;
int up[MAXN][LOG];

// Binary Lifting, Straight fillUp no DFS
void fillUp(int n) {
    for (int l=1; l<LOG; l++) 
        for (int i=1; i<=n; i++) 
            if (up[i][l-1] != -1) up[i][l] = up[up[i][l-1]][l-1];
}

int query(int u, int k) {
    for (int i=0; i<LOG; i++) {
        if (k & (1 << i)) {
            u = up[u][i];
            if (u == -1) break;
        }
    }

    return u;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;

    memset(up, -1, sizeof up);

    for (int i=1, x; i<=n; i++) {
        cin >> x;
        up[i][0] = x;
    };

    fillUp(n);

    while (q--) {
        int u, k;
        cin >> u >> k;

        int ans = query(u, k);
        cout << ans << '\n';
    }

    return 0;
}
