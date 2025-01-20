#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> ans;
int n, m;

void solve(int idx, int val, vector<int>& cur) {
    if (idx > n) {
        ans.push_back(cur);
        return;
    }

    for (int i=val; i<=(m - 10 * (n - idx)); i++) {
        cur.push_back(i);
        solve(idx + 1, i + 10, cur);
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
    solve(1, 1, cur);

    cout << ans.size() << "\n";
    for (auto &v : ans) {
        for (auto &e : v) {
            cout << e << " ";
        }
        cout << "\n";
    }

    return 0;
}