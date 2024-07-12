// https://vjudge.net/problem/UVA-452

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    cin.ignore();
    cin.ignore();
    string sep = "";

    while (tc--)
    {
        cout << sep;
        sep = '\n';
        unordered_map<char, int> idx;
        int cost[30] {}, indegree[30] {};
        vector<vector<int>> adj(30);
        vector<int> dist(30, 0);

        string line, depen;
        char task;
        int tmp_cost, cnt = 0;

        while (getline(cin, line) && line != "") {
            stringstream ss(line);

            ss >> task >> tmp_cost;

            if (idx.find(task) == idx.end()) idx[task] = cnt++;
            cost[idx[task]] = tmp_cost;
            dist[idx[task]] = tmp_cost;

            if (ss >> depen) {
                for (int i=0; i<depen.size(); i++)
                {
                    if (idx.find(depen[i]) == idx.end()) idx[depen[i]] = cnt++;
                    adj[idx[task]].push_back(idx[depen[i]]);
                    indegree[idx[depen[i]]]++;
                }
            }
        }

        queue<int> q;
        int n = cnt;
        for (int i=0; i<n; i++) {
            // cout << i << ": " << indegree[i] << endl;
            if (indegree[i] == 0) q.push(i);
        }

        // cout << "size: " << q.size() << endl; 

        
        
        while (!q.empty())
        {
            int sz = q.size();
            // cout << "sz: " << sz << endl;

            int max_round = 0;
            while (sz--) {
                int u = q.front(); q.pop();
                max_round = max(max_round, cost[u]);

                for (auto &v : adj[u]) {
                    dist[v] = max(dist[v], dist[u] + cost[v]);
                    indegree[v]--;
                    // cout << "indegree: " << indegree[v] << endl;
                    if (indegree[v] == 0) {
                        q.push(v);
                    }
                }
            }
        }

        int ans = 0;
        for (int i=0; i<n; i++) {
            // cout << i << ": " << dist[i] << endl;
            ans = max(ans, dist[i]);
        }

        cout << ans << '\n';
        // if (tc) cout << '\n';
    }

    return 0;
}