// https://atcoder.jp/contests/abc356/tasks/abc356_c

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m, k, arr[105][20];
    char r[105];
    cin >> n >> m >> k;

    for (int i=1; i<=m; i++) {
        cin >> arr[i][0];
        for (int j=1; j<=arr[i][0]; j++) cin >> arr[i][j], arr[i][j]--;
        cin >> r[i];
    }

    int ans = 0;
    for (int mask=0; mask <= (1 << n) - 1; mask++) {
        bool satisfied = true;
        for (int i=1; i<=m; i++) {
            int cnt = 0;
            for (int j=1; j<=arr[i][0]; j++) {
                if (mask & (1 << arr[i][j])) cnt++;
            }
            if (!((r[i] == 'o' && cnt >= k) || (r[i] == 'x' && cnt < k))) satisfied = false;
        }
        if (satisfied) ans++;
    }

    cout << ans << endl;

    return 0;
}