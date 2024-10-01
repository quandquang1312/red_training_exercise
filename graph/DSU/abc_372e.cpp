// https://atcoder.jp/contests/abc372/tasks/abc372_e

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
    #endif

    int n, q; cin >> n >> q;

    map<int, set<int>> mp;
    UnionFind UF(n + 1);
    for (int i=0; i<q; i++) {
        int tp, u, v;
        cin >> tp >> u >> v;

        if (tp == 1) {
            int pu = UF.findSet(u);
            int pv = UF.findSet(v);

            UF.unionSet(u, v);
            int p = UF.findSet(u);

            if (p == pu) {
                for (auto &e : mp[pv]) {
                    mp[p].insert(e);
                }
            } else {
                for (auto &e : mp[pu]) {
                    mp[p].insert(e);
                }
            }

            mp[p].insert(-u);
            mp[p].insert(-v);
            while (mp[p].size() > 10) mp[p].erase(prev(mp[p].end()));
        } else {
            int p = UF.findSet(u);
            int sz = UF.sizeOfSet(p);

            if (sz < v) {
                cout << "-1\n";
                continue;
            }

            if (sz == 1) {
                cout << u << "\n";
                continue;
            }

            int cnt = 1;
            for (auto &e : mp[p]) {
                if (cnt == v) {
                    cout << -e << "\n";
                    break;
                }
                cnt++;
            }
        }
    }

    return 0;
}