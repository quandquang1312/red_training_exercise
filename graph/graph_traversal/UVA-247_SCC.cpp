// https://vjudge.net/problem/UVA-247

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, ans;
vector<int> dfs_num, dfs_low, visited;

stack<int> st;
int timer;

void tarjanSCC(int u)
{
    dfs_low[u] = dfs_num[u] = timer++;
    st.push(u);

    visited[u] = 1;
    for (auto &v : adj[u]) {
        if (dfs_num[v] == -1)
            tarjanSCC(v);
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        vector<int> tmp;
        while (true) {
            int v = st.top(); st.pop();
            tmp.push_back(v);
            visited[v] = 0;
            if (u == v) break;
        }
        // reverse(tmp.begin(), tmp.end());
        ans.push_back(tmp);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m, tc = 0;
    while (cin >> n >> m) {
        if (n + m == 0) break;

        ans.clear();
        adj.assign(n, {});
        timer = 0;
        unordered_map<string, int> idx;
        string ori_name[n];
        while (!st.empty()) st.pop();

        int cnt = 0;
        string a, b;
        for (int i=0; i<m; i++) {
            cin >> a >> b;
            if (idx.find(a) == idx.end()) idx[a] = cnt, ori_name[cnt++] = a;
            if (idx.find(b) == idx.end()) idx[b] = cnt, ori_name[cnt++] = b;

            if (find(adj[idx[a]].begin(), adj[idx[a]].end(), idx[b]) == adj[idx[a]].end())
                adj[idx[a]].push_back(idx[b]);
        }

        // for (int i=0; i<n; i++) {
        //     cout << ori_name[i] << ": " << idx[ori_name[i]] << endl; 
        // }

        // for (int i=0; i<n; i++) {
        //     cout << i << ": ";
        //     for (auto &e : adj[i]) {
        //         cout << e << " ";
        //     }
        //     cout << endl;
        // }

        dfs_num.assign(n, -1);
        dfs_low.assign(n, 0);
        visited.assign(n, 0);
        for (int i=0; i<n; i++) {
            if (dfs_num[i] == -1)
                tarjanSCC(i);
        }

        if (tc) cout << "\n";
        cout << "Calling circles for data set " << ++tc << ":\n";
        // reverse(ans.begin(), ans.end());
        for (int j=0; j<ans.size(); j++) {
            vector<int> vect = ans[j];
            for (int i=0; i<vect.size(); i++) {
                int e = vect[i];
                cout << ori_name[e];
                if (i < vect.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }

    return 0;
}