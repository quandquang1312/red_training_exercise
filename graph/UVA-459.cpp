// https://vjudge.net/problem/UVA-459

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
bool visited[30];

void findCC(int u, int par) {
    if (visited[u]) return;
    visited[u] = true;

    for (auto &v : graph[u]) {
        if (v == par) continue;

        findCC(v, u);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    string first_line;
    while (tc--) {
        char l, a, b; cin >> l;
        cin.ignore();

        int n = l - 64;

        graph.clear();
        graph.resize(n+1);
        memset(visited, 0, sizeof visited);

        string line;
        while (getline(cin, line) && line != "")
        {
            a = line[0], b = line[1];
            graph[a-64].push_back(b-64);
            graph[b-64].push_back(a-64);
        }

        int ans = 0;
        for (int i=1; i<=n; i++) {
            if (!visited[i]) {
                ans++;
                findCC(i,i);
            }
        }

        cout << ans << endl;
        if (tc) cout << endl;
    }

    return 0;
}