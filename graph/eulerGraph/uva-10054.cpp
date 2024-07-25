// https://vjudge.net/problem/UVA-10054

#include <bits/stdc++.h>
using namespace std;

#define MAXN 55

vector<int> hierholzer(int s, const vector<vector<int>>& adj, vector<vector<int>>& visited) {
    vector<int> ans, st;
    st.push_back(s);

    while (!st.empty()) {
        int u = st.back();
        bool fl = false;

        for (auto v : adj[u]) {
            if (!visited[u][v]) {
                visited[u][v] = visited[v][u] = true;
                st.push_back(v);
                fl = true;
                break;
            }
        }

        if (!fl) {
            ans.push_back(u);
            st.pop_back();
        }
    }

    reverse(ans.begin(), ans.end());
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
    for (int idx=1; idx<=tc; idx++) {
        int n; cin >> n;
        vector<vector<int>> adj(MAXN);
        vector<vector<int>> visited(MAXN, vector<int>(MAXN, false));
        for (int i=0; i<n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        bool existEuler = true;
        for (int i=0; i<MAXN; i++) {
            if (adj[i].size() % 2) existEuler = false;
        }

        if (!existEuler) {
            cout << "Case #" << idx << "\n";
            cout << "some beads may be lost\n";
        } else {
            cout << "Case #" << idx << "\n";
            vector<int> eulerPath;
            for (int i=1; i<=MAXN; i++) {
                if (adj[i].size() > 0) {
                    eulerPath = hierholzer(1, adj, visited);
                    break;
                }
            }

            for (int i=0; i<eulerPath.size()-1; i++) {
                cout << eulerPath[i] << " " << eulerPath[i+1] << endl;
            }
        }

        if (idx != tc) cout << "\n";
    }

    return 0;
}