// https://vjudge.net/contest/678673#problem/I

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m;
vector<vector<int>> arr;
vector<vector<int>> ans;

bool isIn(int i, int j) {
    return (i >= 0 && i < n && j >= 0 && j < m);
}

void solve(int i, int j, vector<int>& cur) {
    if (i >= n-1 && j >= m-1) {
        ans.push_back(cur);
        return;
    }

    if (isIn(i + 1, j)) {
        cur.push_back(arr[i+1][j]);
        solve(i + 1, j, cur);
        cur.pop_back();
    }
    if (isIn(i, j + 1)) {
        cur.push_back(arr[i][j+1]);
        solve(i, j + 1, cur);
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
    arr.assign(n, vector<int>(m, 0));

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> arr[i][j];
        }
    }

    vector<int> _;
    solve(0, 0, _);

    sort(ans.begin(), ans.end());

    for (int i=0; i<ans.size(); i++) {
        auto &v = ans[i];
        cout << arr[0][0] << " ";
        for (auto &e : v)
            cout << e << " ";
        cout << "\n";
    }

    return 0;
}