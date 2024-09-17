#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    vector<bool> ans(m + 1, false);
    vector<int> lst(n + 1, -1);
    for (int i=1; i<=m; i++) {
        int ai; char bi;
        cin >> ai >> bi;
        if ((bi == 'M') && (lst[ai] == -1)) {
            lst[ai] = i;
        }
    }

    for (int i=1; i<=n; i++) {
        if (lst[i] != -1) ans[lst[i]] = true;
    }

    for (int i=1; i<=m; i++) {
        cout << (ans[i] == true ? "Yes\n" : "No\n");
    }

    return 0;
}