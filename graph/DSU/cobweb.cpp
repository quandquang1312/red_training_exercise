// https://acm.timus.ru/problem.aspx?space=1&num=1671

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    vector<int> p;
    int numSets;

public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        numSets = N;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    void unionSet(int i, int j, int& noCC)
    {
        if (isSameSet(i, j))
            return;
        noCC--;

        int x = findSet(i), y = findSet(j);
        p[x] = y;
        --numSets;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;

    vector<pair<int, int>> edges(m);
    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        edges[i] = {u, v};
    }

    int q; cin >> q;
    vector<int> queries(q);
    vector<bool> erase(m, false);

    for (int i=0; i<q; i++) {
        int idx; cin >> idx;
        idx--;
        erase[idx] = true;
        queries[i] = idx;
    }

    int noCC = n;
    UnionFind UF(n + 1);
    for (int i=0; i<m; i++) {
        if (erase[i]) continue;
        UF.unionSet(edges[i].first, edges[i].second, noCC);
    }

    vector<int> ans(q);
    for (int i=q-1; i>=0; i--) {
        int idx = queries[i];
        ans[i] = noCC;
        UF.unionSet(edges[idx].first, edges[idx].second, noCC);
    }

    for (int i=0; i<q; i++) {
        cout << ans[i] << (i != q - 1 ? " " : "\n");
    }

    return 0;
}