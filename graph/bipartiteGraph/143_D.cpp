// https://codeforces.com/contest/143/problem/D

#include <bits/stdc++.h>

#define int long long
using namespace std;
 
vector<vector<int>> adj;
vector<int> mt, color, used;
int n, m, c = 1;
 
bool kuhn(int v) {
    if (used[v] == c) return false;
    used[v] = c;

    // faster when using 2 loops
    for (auto &u : adj[v]) {
        if (mt[u] == -1) {
            mt[u] = v;
            return true;
        }
    }

    for (auto &u : adj[v]) {
        if (kuhn(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}
 
 
int flatten(int i, int j) {
    return i * m + j;
}
 
void dfs(int v, int cx) {
    color[v] = cx;
    for (auto u : adj[v]) {
        if (color[u] == -1) dfs(u, cx^1);
    }
}

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> m;

    adj.resize(n * m);
    used.assign(n * m, false);
    color.assign(n * m, -1);
    mt.assign(n * m, -1);

    vector<pair<int, int>> mv = {{-1, -2}, {1, 2}, {-1, 2}, {1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto &[dx, dy] : mv) {
                int new_i = i + dx, new_j = j + dy;
                if (!valid(new_i, new_j)) continue;
                adj[flatten(i, j)].push_back(flatten(dx + i, dy + j));
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < n * m; ++i) {
        if (color[i] != -1) continue;
        dfs(i, 0);
    }

    for (int i = 0; i < n * m; i++) {
        if (color[i]) {
            ans += kuhn(i);
            c++;
        }
    }
    
    cout << n * m - ans;
}