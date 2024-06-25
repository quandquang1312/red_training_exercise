// https://open.kattis.com/problems/builddeps

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> ans;
vector<bool> visited;

void split(vector<string> &ans, string& s)
{
    ans.push_back("");

    for (auto c : s) {
        if (c == ' ') {
            ans.push_back("");
        } else {
            ans.back().push_back(c);
        }
    }
}

void dfs(int v)
{
    if (visited[v]) return;
    visited[v] = true;

    for (auto u : adj[v]) {
        dfs(u);
    }

    ans.push_back(v);
}


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n;
    adj.resize(n+1);
    visited.resize(n+1);

    cin.ignore();
    unordered_map<string, int> idx;
    string cvt[n+1];

    int cnt = 0;
    for (int i=0; i<n; i++) {
        string str;
        getline(cin, str);

        vector<string> v;
        split(v, str);

        v[0] = v[0].substr(0, v[0].size()-1);

        for (auto &e : v) {
            if (idx.find(e) == idx.end()) {
                idx[e] = cnt;
                cvt[cnt] = e;
                cnt++;
            }
        }
        
        for (int i=1; i<v.size(); i++)
            adj[idx[v[i]]].push_back(idx[v[0]]);
    }

    int node;
    string str; cin >> str;
    node = idx[str];

    dfs(node);
    reverse(ans.begin(), ans.end());

    for (auto &e : ans) {
        cout << cvt[e] << endl; 
    }

    return 0;
}