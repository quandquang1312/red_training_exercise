#include <bits/stdc++.h>
using namespace std;

bool visited[100];
vector<vector<int>> CCs;
int CCu[100];
/*
9 7
0 1 // 1
1 2 // 2
1 3 // 3
2 3
3 4 // 5
6 7
7 8 // 7
*/
void findNoCC(int u, int par, vector<int>& cur, vector<vector<int>>& graph) {
    if (visited[u]) return;

    cur.push_back(u);
    CCu[u] = CCs.size() + 1;
    visited[u] = true;

    for (auto &e : graph[u]) {
        if (e == par) continue;

        findNoCC(e, u, cur, graph);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    vector<vector<int>> graph(n);

    int a, b;
    for (int i=0; i<m; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int NoCC = 0;
    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            NoCC++;
            vector<int> cur;
            findNoCC(i, i, cur, graph);
            CCs.push_back(cur);
        }
    }

    cout << "NoCC: " << NoCC << endl;
    for (auto &cc : CCs) {
        for (auto &u : cc) {
            cout << u << " ";
        }
        cout << endl;
    }

    for (int i=0; i<n; i++) {
        cout << i << ": " << CCu[i] << endl;
    }

    return 0;
}