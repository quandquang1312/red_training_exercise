// https://usaco.org/index.php?page=viewproblem2&cpid=669

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define sqr(x) x*x

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

double dist(pair<int, int>& p1, pair<int, int>& p2) {
    double d1 = p1.first - p2.first;
    double d2 = p1.second - p2.second;
    double ans =  sqrt(sqr(d1) + sqr(d2));
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<pair<int, int>> coor(n);

    for (int i=0; i<n; i++) {
        cin >> coor[i].first >> coor[i].second;
    }

    int l = 0, r = 1e9;
    while (l < r) {
        int tmp = (l + r) >> 1;
        double m = tmp * 1.0;

        vector<int> curr;
        curr.push_back(0);

        bool ans = true;
        for (int i=1; i<n; i++) {
            bool possible = false;
            for (int j=0; j<curr.size(); j++) {
                if (dist(coor[i], coor[curr[j]]) <= sqrt(m)) possible = true;
            }
            if (possible == false) {
                ans = false;
                break;
            }
        }

        if (ans) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << endl;

    return 0;
}