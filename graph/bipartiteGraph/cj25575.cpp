// https://codejam.lge.com/problem/25575

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m, e;
        cin >> n >> m >> e;
        vector<pair<int, int>> edges;

        vector<vector<int>> adj(n+m+1);
        vector<int> indegree(n+m+1, 0), marked(n+m+1);
        map<int, int> existIndegreeU, existIndegreeV, minValU, minValV;
        for (int i=0; i<e; i++) {
            int u, v; cin >> u >> v;
            v += n;
            edges.push_back({u, v});
            adj[u].push_back(v);
            adj[v].push_back(u);
            indegree[u]++;
            indegree[v]++;
        }

        vector<pair<int, int>> xsm, ysm;
        for (int i=1; i<=n; i++) {
            if (indegree[i]) {
                existIndegreeU[indegree[i]]++;
                xsm.push_back({indegree[i], i});
            }
        }

        for (int i=n+1; i<=n+m; i++) {
            if (indegree[i]) {
                existIndegreeV[indegree[i]]++;
                ysm.push_back({indegree[i], i});
            }
        }

        sort(xsm.begin(), xsm.end(), greater<>());
        sort(ysm.begin(), ysm.end(), greater<>());

        int val = n, sh = 0;
        for (int i=0; i<xsm.size(); i++, val--) {
            sh += xsm[i].first * val;
            marked[xsm[i].second] = val;
            if (minValU.find(xsm[i].first) == minValU.end()) {
                minValU[xsm[i].first] = val;
            } else {
                minValU[xsm[i].first] = min(minValU[xsm[i].first], val);
            }
        }

        val = m;
        for (int i=0; i<ysm.size(); i++, val--) {
            sh += ysm[i].first * val;
            marked[ysm[i].second] = val;
            if (minValV.find(ysm[i].first) == minValV.end()) {
                minValV[ysm[i].first] = val;
            } else {
                minValV[ysm[i].first] = min(minValV[ysm[i].first], val);
            }
        }

        int mmax = 0;
        for (auto &e : edges) {
            auto [u, v] = e;
            mmax = max(mmax, sh - (marked[u] + marked[v]));
            int tmp_ans = sh;
            if (existIndegreeU[indegree[u]] > 1) {
                tmp_ans -= minValU[indegree[u]];
            } else tmp_ans -= marked[u];

            if (existIndegreeV[indegree[v]] > 1) {
                tmp_ans -= minValV[indegree[v]];
            } else tmp_ans -= marked[v];

            mmax = max(mmax, tmp_ans);
        }

        cout << sh << " " << mmax << "\n";
    }

    return 0;
}