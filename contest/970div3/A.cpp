// https://codeforces.com/contest/2008/problem/A

#include <bits/stdc++.h>
using namespace std;

int n;

bool dfs(int i, vector<int>& vct, int sm) {
    if (i >= n) return (sm == 0); // return

    bool neg = dfs(i + 1, vct, sm - vct[i]);
    bool pos = dfs(i + 1, vct, sm + vct[i]);
    return (neg | pos);
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
        int a, b;
        cin >> a >> b;

        n = a + b;
        vector<int> vct;
        for (int i=0; i<a; i++) vct.push_back(1);
        for (int i=0; i<b; i++) vct.push_back(2);

        bool ans = dfs(0, vct, 0);
        cout << (ans ? "YES\n" : "NO\n");
    }

    return 0;
}