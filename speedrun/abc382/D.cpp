#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> ans;
int n, m;

void solve(int idx, int lstVal, vector<int>& cur) {
    if (lstVal > m) return;

    if (idx >= n) {
        ans.push_back(cur);
        return;
    }

    if (n - idx - 1 != 0) {
        int diff = ((m - (lstVal + 10)) / (n - idx - 1));
        if (diff < 10) return;
    }

    for (int i=lstVal + 10; i <= m; i++) {
        cur.push_back(i);
        solve(idx + 1, i, cur);
        cur.pop_back();
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> m;
    vector<int> cur;
    solve(0, 1-10, cur);

    cout << ans.size() << "\n";
    for (auto &v : ans) {
        for (auto &e : v) {
            cout << e << " ";
        }
        cout << "\n";
    }

    return 0;
}