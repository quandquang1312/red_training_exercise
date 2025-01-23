// https://oj.vnoi.info/problem/dsu_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

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

    int n, m, k; cin >> n >> m >> k;


    DSU dsu(n + 1);

    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
    }

    vector<tuple<int, int, int>> queries(k);
    for (int i=k-1, u, v, f; i>=0; i--) {
        string str; cin >> str;
        cin >> u >> v;
        f = (str[0] == 'a');
        queries[i] = {f, u, v};
    }

    vector<string> ans;
    for (int i=0; i<k; i++) {
        auto [f, u, v] = queries[i];

        if (f == 1) { // ask
            string str = (dsu.isSameSet(u, v) ? "YES" : "NO");
            ans.push_back(str);
        } else {
            dsu.unionSet(u, v);
        }
    }

    reverse(ans.begin(), ans.end());

    for (auto &e : ans) {
        cout << e << "\n";
    }

    return 0;
}