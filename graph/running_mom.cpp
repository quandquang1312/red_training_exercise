// https://open.kattis.com/problems/runningmom

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> colors;
int n;

bool dfs(int v)
{
    colors[v] = 1;
    for (auto u : adj[v]) {
        if (colors[u] == 0) {
            if (dfs(u)) return true;
        } else if (colors[u] == 1) {
            return true;
        }
    }

    colors[v] = 2;
    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n;

    int cnt = 0;
    unordered_map<string, int> idx;

    vector<pair<string, string>> flights;
    vector<string> q;

    for (int i=0; i<n; i++) {
        string src, dst;
        cin >> src >> dst;
        if (idx.find(src) == idx.end()) idx[src] = cnt++;
        if (idx.find(dst) == idx.end()) idx[dst] = cnt++;

        flights.push_back({src, dst});
    }

    cin.ignore();

    string str;
    while (getline(cin, str) && str != "")
    {
        q.push_back(str);
    }

    adj.resize(idx.size() + 10);
    colors.resize(idx.size() + 10);

    for (int i=0; i<flights.size(); i++) {
        adj[idx[flights[i].first]].push_back(idx[flights[i].second]);
    }

    for (int i=0; i<q.size(); i++) {
        if (dfs(idx[q[i]])) {
            cout << q[i] << " safe\n"; 
        } else {
            cout << q[i] << " trapped\n";
        }
    }

    return 0;
}