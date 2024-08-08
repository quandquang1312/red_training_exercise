// https://codejam.lge.com/problem/24433

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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n);
        int max_n = -1;
        for (int i=0; i<n; i++) {
            cin >> arr[i];
            max_n = max(max_n, arr[i]); 
        }

        vector<vector<pair<int, int>>> adj(max_n + 1);
        for (int x=max_n; x>=1; x--) {
            int d = 2;
            while (x % d) x++;

            int y = x / d;
            adj[x].push_back({d, y});
            adj[y].push_back({d, x});
        }

        
    }

    return 0;
}