// https://vjudge.net/problem/UVA-11747

#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> p, rank, setSize;
    int numSets;

public:
    DSU(int n) {
        p.assign(n, 0);
        for (int i=0; i<n; i++) p[i] = i;

        rank.assign(n, 0);
        setSize.assign(n, 1);
        numSets = n;
    }

    int findSet(int i) {
        if (p[i] == i) return i;
        return p[i] = findSet(p[i]);
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    int sizeOfSet(int i) {
        return setSize[findSet(i)];
    }

    int numOfSets() {
        return numSets;
    }

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;

        int x = findSet(i);
        int y = findSet(j);

        if (rank[x] > rank[y]) swap(x, y);

        p[x] = y;
        if (rank[x] == rank[y]) rank[y]++;

        setSize[y] += setSize[x];
        --numSets;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<tuple<int, int, int>> Edges(m);

        for (int i=0, u, v, w; i<m; i++) {
            cin >> u >> v >> w;
            Edges[i] = {w, u, v};
        }

        sort(Edges.begin(), Edges.end());

        DSU dsu(n + 1);

        vector<int> ans;
        for (auto &[w, u, v] : Edges) {
            if (dsu.isSameSet(u, v)) {
                ans.push_back(w);
                continue;
            }

            dsu.unionSet(u, v);
        }

        if (ans.empty()) {
            cout << "forest\n";
        } else {
            for (int i=0; i<ans.size(); i++) {
                if (i) cout << " ";
                cout << ans[i];
            }
            cout << "\n";
        }
    }

    return 0;
}