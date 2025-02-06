// https://codeforces.com/contest/2020/problem/D

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

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<vector<int>> dp(n + 1, vector<int>(10 + 1, 0));
        for (int i=0, a, d, k; i<m; i++) {
            cin >> a >> d >> k;

            dp[a][d]++;
            dp[a + d * k][d]--;
        }


        DSU dsu(n + 1);

        for (int i=1; i<=n; i++) {
            for (int d=1; d<=10; d++) {
                if (i < d) continue;

                if (dp[i - d][d] > 0) {
                    dp[i][d] += dp[i - d][d];
                    dsu.unionSet(i - d, i);
                }
            }
        }

        int ans = dsu.numOfSets() - 1;
        cout << ans << "\n"; 
    }

    return 0;
}