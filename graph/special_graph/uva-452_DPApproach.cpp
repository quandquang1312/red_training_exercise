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
                }
            }
        }

    }

    return 0;
}