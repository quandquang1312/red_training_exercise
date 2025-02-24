// https://atcoder.jp/contests/abc394/tasks/abc394_e

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<string> graph(n);

    for (int i=0; i<n; i++) {
        cin >> graph[i];
    }

    vector<vector<vector<int>>> in(n, vector<vector<int>>(26)), out(n, vector<vector<int>>(26));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (graph[i][j] != '-') {
                int c = graph[i][j] - 'a';
                out[i][c].push_back(j);
                in[j][c].push_back(i);
            }
        }
    }

    queue<pair<int, int>> q;

    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i=0; i<n; i++) {
        dp[i][i] = 0;
        q.push({i, i});
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (graph[i][j] != '-') {
                dp[i][j] = min(dp[i][j], 1);
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto &[s, t] = q.front(); q.pop();

        for (int c=0; c<26; c++) {
            for (auto &u : in[s][c]) {
                for (auto &v : out[t][c]) {
                    if (dp[u][v] > dp[s][t] + 2) {
                        dp[u][v] = dp[s][t] + 2;
                        q.push({u, v});
                    }
                }
            }
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << (dp[i][j] == INF ? -1 : dp[i][j]) << " "; 
        }
        cout << "\n";
    }

    return 0;
}