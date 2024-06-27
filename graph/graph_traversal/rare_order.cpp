// https://vjudge.net/problem/UVA-200

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<set<int>> adj;
vector<bool> visited;
vector<int> topo;

void dfs(int v)
{
    if (visited[v]) return;
    visited[v] = true;

    for (auto &u : adj[v]) {
        dfs(u);
    }

    topo.push_back(v);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    vector<string> inp;
    string str;
    while (getline(cin, str) && str != "#")
    {
        inp.push_back(str);
    }

    int cnt = 0;
    char cvt[21];
    unordered_map<char, int> idx;
    for (int i=0; i<inp.size(); i++) {
        for (auto &c : inp[i]) {
            if (idx.find(c) == idx.end()) {
                idx[c] = cnt;
                cvt[cnt] = c;
                cnt++;
            }
        }
    }

    n = cnt;
    adj.resize(n+1);
    visited.resize(n+1, false);

    for (int i=0; i<inp.size(); i++) {
        for (int j=i+1; j<inp.size(); j++) {
            int k = 0;
            while ((k<inp[i].size() && k<inp[j].size()) && (inp[i][k] == inp[j][k])) k++;
            if (k >= inp[i].size() || k >= inp[j].size()) continue;
            adj[idx[inp[i][k]]].insert(idx[inp[j][k]]);
        }
    }

    // for (auto &e : idx) {
    //     cout << e.first << "-" << e.second << endl;
    // }

    // for (int i=0; i<n; i++) {
    //     cout << i << ": ";
    //     for (auto &u : adj[i]) {
    //         cout << u << ", ";
    //     }
    //     cout << endl;
    // }

    for (int i=0; i<n; i++) {
        if (!visited[i]) dfs(i);
    }

    reverse(topo.begin(), topo.end());

    for (auto &v : topo)
    {
        cout << cvt[v];
    }
    cout << endl;

    return 0;
}