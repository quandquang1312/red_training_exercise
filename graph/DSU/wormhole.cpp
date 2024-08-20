// https://usaco.org/index.php?page=viewproblem2&cpid=992
/*
- DSU to gather the node that can connected to each other (has hole to go to another - with the condition 
- to perform binary search on the width) to a set
- If any cow i is in the position j, then if i and j is not in the same set, it can not be sorted
- Use binary search to find the minimum width required to sort the cows
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 100020

struct wormhole {
    int x, y, w;
};

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
        freopen("wormsort.in", "r", stdin);
        freopen("wormsort.out", "w", stdout);
    #endif

    int n, m, cows[MAXN], max_w = 0;

    cin >> n >> m;
    for (int i=1; i<=n; i++) cin >> cows[i];

    vector<wormhole> holes(m);
    for (int i=0; i<m; i++) {
        cin >> holes[i].x >> holes[i].y >> holes[i].w;
        max_w = max(max_w, holes[i].w);
    }

    int l = 0, r = max_w + 1;
    while (l < r) {
        int middle = (l + r + 1) >> 1;

        UnionFind UF(n + 1);
        for (auto &hole : holes) {
            if (hole.w >= middle) {
                UF.unionSet(hole.x, hole.y);
            }
        }

        bool ans = true;
        for (int i=1; i<=n; i++) {
            if (!UF.isSameSet(cows[i], i)) {
                ans = false;
                break;
            }
        }

        if (ans) {
            l = middle;
        } else {
            r = middle - 1;
        }
    }

    cout << (l == max_w + 1 ? -1 : l) << endl;


    return 0;
}