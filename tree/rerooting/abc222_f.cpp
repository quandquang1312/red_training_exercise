// https://atcoder.jp/contests/abc222/tasks/abc222_f

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<pair<int, int>>> adj;
vector<vector<pair<int, int>>> dp; 
vector<int> D, ans;

void dfs(int u, int par) {
    vector<pair<int, int>> tmp;
    for (auto &[v, w] : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
        if (dp[v].size() == 0) {
            tmp.push_back({v, w});
        } else {
            tmp.push_back({dp[v][0].first, w + dp[v][0].second});
        }
    }

    if (tmp.empty()) {
        dp[u].clear();
    } else {
        sort(tmp.begin(), tmp.end(), [](pair<int, int> p1, pair<int, int> p2) {
            return p1.second + p1.first < p2.second + p2.first;
        });

        if (tmp.size() >= 2) {
            dp[u].push_back(tmp[tmp.size() - 1]);
            dp[u].push_back(tmp[tmp.size() - 2]);
        } else if (tmp.size() == 1) {
            dp[u].push_back(tmp[0]);
        }
    }
}

void rerooting(int u, int par, int dw) {
    ans[u] = D[dp[u][0].first] + dp[u][0].second;

    for (auto &[v, w] : adj[u]) {
        if (v == par) continue;

        // detach v from u
        vector<pair<int, int>> o_u = dp[u], o_v = dp[v];
        dp[u].clear();
        // dp[v].clear();

        vector<pair<int, int>> tmp;
        for (auto [tmp_v, tmp_w] : adj[u]) {
            if (v == tmp_v) continue;
            if (!dp[tmp_v].empty()) tmp.push_back({dp[tmp_v][0].first, tmp_w + dp[tmp_v][0].second});
            else tmp.push_back({tmp_v, tmp_w});
        }

        sort(tmp.begin(), tmp.end(), [](pair<int, int> p1, pair<int, int> p2) {
            return p1.second + p1.first < p2.second + p2.first;
        });

        if (tmp.size() >= 2) {
            dp[u].push_back(tmp[tmp.size() - 1]);
            dp[u].push_back(tmp[tmp.size() - 2]);
        } else if (tmp.size() == 1) {
            dp[u].push_back(tmp[0]);
        }

        // attack u to v
        if (dp[u].size()) dp[v].push_back({dp[u][0].first, w + dp[u][0].second});
        if (!dp[v].size()) dp[v].push_back({u, w + D[u]});

        sort(dp[v].begin(), dp[v].end(), [](pair<int, int> p1, pair<int, int> p2) {
            return p1.second + p1.first < p2.second + p2.first;
        });

        reverse(dp[v].begin(), dp[v].end());
        dp[v].resize(2);

        // reroot
        rerooting(v, u, w);

        // backtrack
        dp[u] = o_u, dp[v] = o_v;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    adj.resize(n + 1);
    D.resize(n + 1);
    ans.resize(n + 1);
    dp.assign(n + 1, vector<pair<int, int>>());

    for (int i=1, u, v, w; i<n; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for (int i=1, d; i<=n; i++) cin >> D[i];

    dfs(1, 0);
    rerooting(1, 0, 0);

    for (int i=1; i<=n; i++) {
        cout << ans[i] << "\n";
        // for (auto &e : dp[i]) {
        //     cout << " - " << e.second + D[e.first] << "\n";
        // }
    }

    return 0;
}