// https://codejam.lge.com/problem/25123

#include <bits/stdc++.h>
using namespace std;

#define int long long

void sub_2(int n, string tr, vector<int> par) {
    vector<pair<int, int>> subans(n + 1, {-1, -1});
    vector<pair<int, int>> subans2(n + 1, {-1, -1});
    vector<vector<int>> adj(n+1);
    vector<int> indegree(n+1, 0);
    queue<int> q;

    for (int i=1; i<=n; i++) {
        if (par[i] == 0 || tr[i] == tr[par[i]]) continue;
        adj[par[i]].push_back(i);
        adj[i].push_back(par[i]);
        indegree[i]++;
        indegree[par[i]]++;
    }

    for (int i=1; i<=n; i++) {
        if (indegree[i] == 1) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        subans[u] = {1, 1};
        subans2[u] = {1, 1};

        vector<pair<int, int>> tmp_vect;

        for (auto &v : adj[u]) {
            if (indegree[v] != 0) {
                indegree[u]--;
                indegree[v]--;
            }
            
            if (indegree[v] == 1) q.push(v);
            if (indegree[v] != 0) continue;

            // cout << u << "->" << v << '\n';

            pair<int, int> sa2 = subans2[v];
            if (u == 1) cout << u << " -> " << v << "_" << sa2.first << ";" << sa2.second << "\n";
            if (sa2.first + 1 > subans2[u].first) subans2[u] = {sa2.first + 1, sa2.second};
            else if (sa2.first + 1 == subans2[u].first) subans2[u] = {sa2.first, sa2.second + 1};

            pair<int, int> sa = subans[v];
            tmp_vect.push_back(sa);
        }

        if (tmp_vect.size() == 1) {
            subans[u] = {tmp_vect[0].first + 1, tmp_vect[0].second};
            subans2[u] = {tmp_vect[0].first + 1, tmp_vect[0].second};
        } else if (tmp_vect.size() > 1) {
            sort(tmp_vect.begin(), tmp_vect.end(), [](pair<int, int> p1, pair<int, int> p2){
                return p1.first > p2.second;
            });

            int fmax = tmp_vect[0].first, i = 0;
            while (fmax == tmp_vect[i].first) i++;
            if (i < tmp_vect.size()) {
                if (i == 1) { // only 1 max
                    int tmp_ans = tmp_vect[0].second, sm = 0;
                    for (int j=1; tmp_vect[j].first==tmp_vect[1].first; j++) {
                        sm += tmp_vect[j].second;
                    }
                    tmp_ans *= sm;
                    subans[u] = {tmp_vect[0].first + tmp_vect[1].first + 1, tmp_ans};
                } else { // multiple max
                    int tmp_ans = tmp_vect[0].second;
                    for (int j=1; tmp_vect[j].first==tmp_vect[0].first; j++) {
                        tmp_ans *= tmp_vect[j].second;
                    }
                    subans[u] = {tmp_vect[0].first * 2 + 1, tmp_ans};
                }
            }
        } else {

        }

        cout << u << ": " << subans[u].first << " . " << subans[u].second << '\n';
        cout << u << ": " << subans2[u].first << " . " << subans2[u].second << '\n';
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
    while (tc--) {
        int n; cin >> n;
        string tr; cin >> tr;
        tr = '0' + tr;
        vector<int> par(n + 1);
        for (int i=1; i<=n; i++) cin >> par[i];
        sub_2(n, tr, par);
    }

    return 0;
}