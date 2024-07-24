// https://vjudge.net/problem/UVa-12644

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;

vector<int> adj[MAXN];
bool visited[MAXN];
int RightMatch[MAXN], LeftMatch[MAXN];

bool check(string s1, string s2) {
    int cnt1[30] {}, cnt2[30] {};
    for (auto &e : s1) cnt1[e - 'a']++;
    for (auto &e : s2) cnt2[e - 'a']++;

    for (int i=0; i<30; i++) if (cnt1[i] < cnt2[i]) return false;

    return true;
}

bool kuhn(int u) {
    for (int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i];

        if (visited[v]) continue;
        visited[v] = true;

        if (RightMatch[v] == -1 || kuhn(RightMatch[v]) == true) {
            RightMatch[v] = u;
            LeftMatch[u]  = v;
            return true;
        }
    }

    return false;
}

int solve(int m) {
    int matching = 0;
    while (true) {
        memset(visited, false, sizeof visited);
        bool foundMatch = false;

        for (int i=0; i<m; i++) {
            if (LeftMatch[i] != -1) continue;
            if (kuhn(i)) foundMatch = true, matching++;
        }

        if (foundMatch == false) break;
    }

    return matching;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m;
    while (cin >> n >> m) {
        vector<string> Jack(n), Jill(m);

        for (int i=0; i<MAXN; i++) {
            adj[i].clear();
            RightMatch[i] = LeftMatch[i] = -1;
        }

        for (int i=0; i<n; i++) cin >> Jack[i];
        for (int i=0; i<m; i++) cin >> Jill[i];
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (check(Jack[i], Jill[j])) adj[j].push_back(m + i);
            }
        }

        int ans = solve(m);
        cout << ans << endl;
    }

    return 0;
}