// https://codeforces.com/problemset/problem/1513/D
 
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
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
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, p;
        cin >> n >> p;

        vector<int> arr(n);
        vector<pair<int, int>> b(n);
        vector<tuple<int, int, int>> EL;

        for (int i=0; i<n; i++) {
            cin >> arr[i];
            b[i] = {arr[i], i};
            if (i < n - 1) EL.push_back({p, i, i + 1});
        }

        sort(b.begin(), b.end());

        UnionFind UF(n + 1);
        for (auto &[v, i] : b) {
            if (v < p) {
                for (int j=i-1; j>=0; j--) {
                    if (arr[j] % arr[i] == 0 && !UF.isSameSet(i, j)) {
                        UF.unionSet(i, j);
                        EL.push_back({arr[i], i, j});
                    } else {
                        break;
                    }
                }

                for (int j=i+1; j<n; j++) {
                    if (arr[j] % arr[i] == 0 && !UF.isSameSet(i, j)) {
                        UF.unionSet(i, j);
                        EL.push_back({arr[i], i, j});
                    } else {
                        break;
                    }
                }
            } else {
                break;
            }
        }

        sort(EL.begin(), EL.end());

        UnionFind newUF(n + 1);

        int mst = 0, cnt = 0;
        for (auto &[w, u, v] : EL) {
            if (newUF.isSameSet(u, v)) continue;
            mst += w;
            cnt++;
            newUF.unionSet(u,v);

            if (cnt == n - 1) break;
        }

        cout << mst << '\n';
    }
    return 0;
}