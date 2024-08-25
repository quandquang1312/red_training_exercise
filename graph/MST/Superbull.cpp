// https://usaco.org/index.php?page=viewproblem2&cpid=531

#include <bits/stdc++.h>
using namespace std;

#define int long long

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
    #else
        freopen("superbull.in", "r", stdin);
        freopen("superbull.out", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);
    vector<tuple<int, int, int>> EL;

    for (auto &e : arr) cin >> e;

    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            int w = (arr[i] ^ arr[j]);
            EL.push_back({-w, i + 1, j + 1});
        }
    }

    sort(EL.begin(), EL.end());

    UnionFind UF(n + 1);
    int mst = 0, cnt = 0;

    for (auto &[w, u, v] : EL) {
        if (UF.isSameSet(u, v)) continue;
        w = -w;
        mst += w;
        cnt++;
        UF.unionSet(u, v);

        if (cnt == n-1) break;
    }

    cout << mst << '\n';

    return 0;
}