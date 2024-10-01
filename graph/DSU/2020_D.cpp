// https://codeforces.com/contest/2020/problem/D

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

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<vector<int>> dp(n + 1, vector<int>(12));
        for (int i=0, a, d, k; i<m; i++) {
            cin >> a >> d >> k;

            // different array with the second parameter is d
            dp[a][d]++;
            dp[a + d * k][d]--;
        }

        UnionFind UF(n + 1);
        // find for each points does it connect to any node
        // via the gaps of d
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=10; j++) {
                // check if i connect to some nodes before it
                // via the gap of j
                if (i > j) dp[i][j] += dp[i-j][j];
                
                // if it is connect
                if (dp[i][j] > 0) {
                    UF.unionSet(i, i+j);
                }
            }
        }

        int ans = 0;
        for (int i=1; i<=n; i++) {
            int p = UF.findSet(i);
            if (p == i) ans++;
        }

        cout << ans << "\n";
    }

    return 0;
}