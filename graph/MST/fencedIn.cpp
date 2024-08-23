// https://usaco.org/index.php?page=viewproblem2&cpid=623

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    vector<int> p;

public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j)
    {
        if (isSameSet(i, j))
            return;
        int x = findSet(i), y = findSet(j);
        p[x] = y;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #else
        freopen("fencedin.in", "r", stdin);
        freopen("fencedin.out", "w", stdout);
    #endif

    int a, b, n, m;
    cin >> a >> b >> n >> m;

    int total_cell = (n + 1) * (m + 1);
    vector<tuple<int, int, int>> EL;

    int ver_arr[n+1], hor_arr[m+1];

    for (int i=0; i<n; i++) cin >> ver_arr[i];
    for (int i=0; i<m; i++) cin >> hor_arr[i];

    ver_arr[n] = a;
    hor_arr[m] = b;

    sort(ver_arr, ver_arr + n + 1);
    sort(hor_arr, hor_arr + m + 1);

    int64_t lst = 0;
    for (int i=0, cur; i<=n; i++) {
        cur = ver_arr[i];
        ver_arr[i] = (cur - lst);
        lst = cur;
    }

    lst = 0;
    for (int i=0, cur; i<=m; i++) {
        cur = hor_arr[i];
        hor_arr[i] = (cur - lst);
        lst = cur;
    }

    for (int i=1; i<=total_cell; i++) {
        int c = (i - 1) % (n + 1);
        int r = (i / (n + 1)) - (i % (n + 1) ? 0 : 1);

        if (i % (n + 1) != 0) EL.push_back({hor_arr[r], i, i+1}); // right
        if (i <= total_cell - (n + 1)) EL.push_back({ver_arr[c], i, i + (n + 1)}); // down
    }

    sort(EL.begin(), EL.end());
    UnionFind UF(total_cell + 5);
    int64_t mst = 0, cnt = 0;
    for (auto &[w, u, v] : EL) {
        if (UF.isSameSet(u,v)) continue;

        mst += w;
        cnt += 1;

        UF.unionSet(u, v);

        if (cnt == total_cell - 1) break;
    }

    cout << mst << '\n';

    return 0;
}