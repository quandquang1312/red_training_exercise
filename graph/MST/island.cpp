// https://open.kattis.com/problems/islandhopping

#include <bits/stdc++.h>
using namespace std;

#define int long long

class UnionFind
{
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

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n;
        cin >> n;
        vector<pair<double, double>> coor(n);

        for (int i = 0; i < n; i++)
            cin >> coor[i].first >> coor[i].second;
        vector<tuple<double, int, int>> adj;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;

                double f = (coor[i].first - coor[j].first), s = (coor[i].second - coor[j].second);
                double distance = sqrt(f * f + s * s);

                adj.push_back({distance, i, j});
            }
        }

        sort(adj.begin(), adj.end());

        UnionFind UF(n);

        double mst_cost = 0.0;
        int cnt = 0;
        for (auto &[w, u, v] : adj)
        {
            if (UF.isSameSet(u, v))
                continue;
            mst_cost += w;

            UF.unionSet(u, v);
            cnt++;
            if (cnt == n - 1)
                break;
        }

        cout << fixed;
        cout.precision(4);
        cout << mst_cost << endl;
    }

    return 0;
}