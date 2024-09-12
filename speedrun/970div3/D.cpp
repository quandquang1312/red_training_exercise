// https://codeforces.com/contest/2008/problem/D

#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;
vector<int> arr, color;

int dfs(int u, vector<int>& CC) {
    if (visited[u]) return 0;
    visited[u] = true;

    CC.push_back(u);

    int ans = (color[u] == 0);
    ans += dfs(arr[u], CC);
    return ans;
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
        int n; cin >> n;
        
        arr.assign(n + 1, 0);
        color.assign(n + 1, 0);
        visited.assign(n + 1, false);

        for (int i=0; i<n; i++) cin >> arr[i + 1];
        string str; cin >> str;

        for (int i=0; i<n; i++) color[i + 1] = (str[i] == '1');

        vector<int> ans(n + 1, 0);
        for (int i=1; i<=n; i++) {
            if (visited[i] == false) {
                vector<int> CC;
                ans[i] = dfs(i, CC);
                for (auto &u : CC) ans[u] = ans[i];
            }
        }

        for (int i=1; i<=n; i++) {
            cout << ans[i] << " "; 
        }

        cout << endl;
    }

    return 0;
}