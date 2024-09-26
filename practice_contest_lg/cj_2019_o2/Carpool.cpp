// https://codejam.lge.com/problem/17280

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200010

bool visited[MAXN];
int RightMatch[MAXN], LeftMatch[MAXN];

bool kuhn(int u, vector<vector<int>>& adj) {
    for (int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i];

        if (visited[v]) continue;
        visited[v] = true;

        if (RightMatch[v] == -1 || kuhn(RightMatch[v], adj) == true) {
            RightMatch[v] = u;
            LeftMatch[u]  = v;
            return true;
        }
    }

    return false;
}

int maximum_matching(int m, vector<vector<int>>& adj) {
    int matching = 0;
    while (true) {
        memset(visited, false, sizeof visited);
        bool foundMatch = false;

        for (int i=0; i<m; i++) {
            if (LeftMatch[i] != -1) continue;
            if (kuhn(i, adj)) foundMatch = true, matching++;
        }

        if (foundMatch == false) break;
    }

    return matching;
}

int solve_greedy(vector<int>& riders, vector<pair<int, int>>& drivers) {
    multiset<int> ms(riders.begin(), riders.end());

    // Sort by end point to maximum the later options
    sort(drivers.begin(), drivers.end(), [] (pair<int, int> p1, pair<int, int> p2) {
        if (p1.second == p2.second) return p1.first < p2.first;
        return p1.second < p2.second;
    });

    // matching each drivers with the available rider.
    // if can't, it means we can't match this driver, ignore him
    int ans = 0;
    for (auto &e : drivers) {
        auto it = ms.lower_bound(e.first);
        if (it == ms.end() || *it > e.second) continue;
        ans++;
        ms.erase(it);
    }

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
        int n, m; cin >> n >> m;

        memset(visited, false, sizeof visited);
        for (int i=0; i<MAXN; i++) {
            RightMatch[i] = LeftMatch[i] = -1;
        }

        vector<int> riders(n), riders_rev(n);
        for (int i=0; i<n; i++) {
            cin >> riders[i];
            riders_rev[i] = -riders[i];
        }

        vector<pair<int, int>> drivers(m);
        for (auto &e : drivers) cin >> e.first >> e.second;

        sort(riders.begin(), riders.end());
        sort(riders_rev.begin(), riders_rev.end());

        // * for bipartitie maximum matching implementation
        // vector<vector<int>> adj(m + n);
        // for (int i=0; i<m; i++) {
        //     auto e = drivers[i];

        //     for (int j=0; j<n; j++) {
        //         if (e.first <= riders[j] && riders[j] <= e.second) {
        //             adj[i].push_back(m + j);
        //             adj[m + j].push_back(i);
        //         }
        //     }
        // }

        // int ans = maximum_matching(m, adj);
        // cout << ans << endl;
    
        int ans = solve_greedy(riders,drivers);
        cout << ans << endl;
    }

    return 0;
}