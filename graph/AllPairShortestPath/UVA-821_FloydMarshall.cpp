// https://vjudge.net/problem/UVA-821

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int a, b, cnt = 1, tc = 1;
    vector<vector<int>> mat(105, vector<int>(105, 1e9));
    unordered_map<int, int> idx;
    while (cin >> a >> b) {
        if (a + b == 0) {
            if (cnt == 1) break;
            int n = idx.size() + 1;
            // cout << "n: " << n << endl;
            for (int k=1; k<=n; k++)
                for (int i=1; i<=n; i++)
                    for (int j=1; j<=n; j++)
                        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

            double sm = 0.0;
            for (int i=1; i<=n; i++) {
                for (int j=1; j<=n; j++) {
                    if (mat[i][j] == 1e9) continue;
                    sm += mat[i][j] * 1.0;
                }
            }

            // cout << "sm: " << sm << endl;
            printf("Case %d: ", tc++);
            printf("average length between pages = %.3f clicks\n", sm/((n-1)*(n-2)));
            mat.assign(105, vector<int>(105, 1e9));
            idx.clear();
            cnt = 1;
        } else {
            if (idx.find(a) == idx.end()) idx[a] = cnt++;
            if (idx.find(b) == idx.end()) idx[b] = cnt++;
            mat[idx[a]][idx[b]] = 1;
            mat[idx[a]][idx[a]] = 0;
            mat[idx[b]][idx[b]] = 0;
        }
    }

    return 0;
}