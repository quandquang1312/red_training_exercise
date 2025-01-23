// https://oj.vnoi.info/problem/dsu_b

#include <bits/stdc++.h>
using namespace std;

#define int long long

class DSU {
private:
    vector<int> p, rank, setSize;
    vector<int> maxIn, minIn;
    int numSets;

public:
    DSU(int n) {
        p.assign(n, 0);
        for (int i=0; i<n; i++) p[i] = i;

        rank.assign(n, 0);
        setSize.assign(n, 1);
        maxIn.assign(n, 0);
        minIn.assign(n, 1e9);

        iota(maxIn.begin(), maxIn.end(), 0);
        iota(minIn.begin(), minIn.end(), 0);

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

    int getMax(int i) {
        return maxIn[findSet(i)];
    }

    int getMin(int i) {
        return minIn[findSet(i)];
    }

    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;

        int x = findSet(i);
        int y = findSet(j);

        if (rank[x] > rank[y]) swap(x, y);

        p[x] = y;

        maxIn[y] = max(maxIn[x], maxIn[y]);
        minIn[y] = min(minIn[x], minIn[y]);

        if (rank[x] == rank[y]) rank[y]++;

        setSize[y] += setSize[x];
        --numSets;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    DSU dsu(n + 1);

    for (int i=0; i<m; i++) {
        string str; cin >> str;

        if (str[0] == 'u') {
            int u, v; cin >> u >> v;
            dsu.unionSet(u, v);
        } else {
            int u; cin >> u;
            int mmin = dsu.getMin(u);
            int mmax = dsu.getMax(u);
            int nos = dsu.sizeOfSet(u); 

            cout << mmin << " " << mmax << " " << nos << "\n";
        }
    }

    return 0;
}