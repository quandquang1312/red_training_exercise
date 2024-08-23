// https://vjudge.net/problem/UVA-908

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    vector<int> p, rank, setSize;
    int numSets;

public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        rank.assign(N, 0);
        setSize.assign(N, 1);
        numSets = N;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
    void unionSet(int i, int j)
    {
        if (isSameSet(i, j))
            return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y])
            swap(x, y);
        p[x] = y;
        if (rank[x] == rank[y])
            ++rank[y];
        setSize[y] += setSize[x];
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

    int n;
    bool sp = false;
    while (cin >> n) {
        if (sp) puts("");
        sp = true;
        vector<tuple<int, int, int>> choosen, newline, original;

        int current_cost = 0;
        for (int i=0, u, v, w; i<n-1; i++) {
            cin >> u >> v >> w;
            choosen.push_back({w, u, v});
            current_cost += w;
        }

        int k; cin >> k;
        for (int i=0, u, v, w; i<k; i++) {
            cin >> u >> v >> w;
            newline.push_back({w, u, v});
        }

        int q; cin >> q;
        for (int i=0, u, v, w; i<q; i++) {
            cin >> u >> v >> w;
            original.push_back({w, u, v});
        }
        for (auto &e : newline) original.push_back(e);

        sort(original.begin(), original.end());

        int new_cost = 0, cnt = 0;
        UnionFind UF(n + 1);
        for (auto &[w, u, v] : original) {
            if (UF.isSameSet(u, v)) continue;
            new_cost += w;
            UF.unionSet(u, v);
            cnt++;

            if (cnt == n - 1) break;
        }

        printf("%d\n%d\n", current_cost, new_cost);
    }

    return 0;
}