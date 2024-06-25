// https://vjudge.net/problem/UVA-872

#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;
vector<int> indegree;
vector<string> rs;
int n;

void backtrack(vector<int>& res, vector<vector<int>>& adj, char cvt[])
{
    for (int i=1; i<=n; i++)
    {
        if (indegree[i] == 0 && !visited[i])
        {
            for (auto u : adj[i])
                indegree[u]--;

            res.push_back(i);
            visited[i] = true;

            backtrack(res, adj, cvt);

            res.pop_back();
            visited[i] = false;

            for (auto u : adj[i])
                indegree[u]++;
        }
    }

    if (res.size() == n) {
        string str;
        for (int i=0; i<n; i++) {
            str.push_back(cvt[res[i]]);
        }
        rs.push_back(str);
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
    cin.ignore();

    auto getNode = [](string str) {
        vector<char> ans;
        for (auto c : str)
            if (c != ' ') ans.push_back(c);

        return ans;
    };

    while (tc--)
    {
        cin.ignore();
        string line;
        getline(cin, line);
        // istringstream iss(in);
        // // while (iss >> in)
        // //     line.push_back(in[0]);

        vector<char> nodes = getNode(line);

        n = nodes.size();
        vector<vector<int>> adj(n+1);
        visited.resize(n+1, false);
        indegree.resize(n+1, 0);

        unordered_map<char, int> idx;

        int cnt = 1;
        char cvt[25];

        for (auto &c : nodes) {
            if (idx.find(c) == idx.end()) {
                idx[c] = cnt;
                cvt[cnt] = c;
                cnt++;
            }
        }

        // getline(cin, in);
        // iss.clear();
        // iss.str(in);
        cin.ignore();
        line.clear();
        getline(cin, line);

        for (int i=1; i<line.size()-1; i++) {
            char a = line[i-1];
            char b = line[i+1];
            if (line[i] == '<') {
                adj[idx[a]].push_back(idx[b]);
                indegree[idx[b]]++;
            }
        }

        for (int v=1; v<=n; v++) {
            cout << v << ": ";
            for (auto &u : adj[v]) {
                cout << u << " ";
            }
            cout << endl;
        }

        vector<int> res;
        backtrack(res, adj, cvt);

        sort(rs.begin(), rs.end());

        for (int i=0; i<rs.size(); i++) {
            for (auto &c : rs[i]) {
                cout << c << " ";
            }
            cout << endl;
        }

        rs.clear();
        if (tc) cout << endl;
    }

    return 0;
}