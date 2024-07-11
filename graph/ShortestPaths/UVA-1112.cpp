    // https://vjudge.net/problem/UVA-1112

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
        for (int t=0; t<tc; t++)
        {
            if (t) printf("\n");
            int n, e, s, m;
            cin >> n >> e >> s >> m;

            vector<int> dist(n+1, 1e9);
            dist[e] = 0;
            vector<vector<pair<int, int>>> AL(n+1); //, vector<pair<int, int>>(0));
            for (int i=0; i<m; i++) {
                int u, v, w;
                cin >> u >> v >> w;
                AL[v].push_back({u, w});
            }

            priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int, int>>> pq;
            pq.push({dist[e], e});

            while (!pq.empty())
            {
                auto [d, u] = pq.top();
                pq.pop();

                if (d > dist[u]) continue;
                for (auto &[v, w] : AL[u]) {
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }

            int ans = 0;
            for (int i=1; i<=n; i++)
                ans += (dist[i] <= s);

            printf("%d\n", ans);
        }

        return 0;
    }