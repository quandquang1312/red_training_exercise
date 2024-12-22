// https://vjudge.net/contest/678673#problem/J

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e18

int x, n, m, ans = INF;
vector<vector<int>> C;

bool check(vector<int>& cur) {
    for (int i=1; i<=m; i++) if (cur[i] < x) return false;
    return true;
}

void solve(int idx, vector<int>& cur, int& sm) {
    if (idx >= n) {
        if (check(cur)) ans = min(ans, sm);
        return;
    }

    // skip
    solve(idx + 1, cur, sm);

    // choose
    for (int i=1; i<=m; i++) cur[i] += C[idx][i];
    sm += C[idx][0];

    solve(idx + 1, cur, sm);
    for (int i=1; i<=m; i++) cur[i] -= C[idx][i];
    sm -= C[idx][0];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> m >> x;

    C.assign(n, vector<int>(m + 1));

    for (int i=0; i<n; i++) {
        for (int j=0; j<=m; j++)
            cin >> C[i][j];
    }

    vector<int> cur(m + 1, 0);
    int sm = 0;
    solve(0, cur, sm);

    cout << (ans == INF ? -1 : ans) << "\n";

    return 0;
}