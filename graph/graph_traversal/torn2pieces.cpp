// https://open.kattis.com/problems/torn2pieces

#include <bits/stdc++.h>
using namespace std;

unordered_map<string, set<string>> adj;
vector<bool> visited;
int n;

vector<string> split(string& s)
{
    vector<string> ans;

    string str = "";
    for (auto &c : s) {
        if (c == ' ') {
            ans.push_back(str);
            str = "";
        } else str.push_back(c);
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n;

    cin.ignore();
    for (int i=0; i<n; i++) {
        string line;
        getline(cin, line);

        vector<string> v = split(line);

        for (int j=1; j<v.size(); j++) {
            adj[v[0]].insert(v[j]);
            adj[v[0]].insert(v[j]);
        }
    }

    string st, en;
    cin >> st >> en;

    

    return 0;
}