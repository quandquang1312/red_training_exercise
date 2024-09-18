// https://cses.fi/problemset/task/1723
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N 105

const int INF = 2e18;

struct Matrix { 
    int mat[MAX_N][MAX_N];
};

Matrix gen(int n) {
    Matrix ans;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            ans.mat[i][j] = INF;

    return ans;
}

Matrix matMul(Matrix a, Matrix b) {
    Matrix ans; int i, j, k;

    for (i = 0; i < MAX_N; i++) {
        for (j = 0; j < MAX_N; j++) {
            for (k = 0; k < MAX_N; k++) {
                if (ans.mat[i][j] == 0) ans.mat[i][j] = a.mat[i][k] + b.mat[k][j];
                else ans.mat[i][j] = min(ans.mat[i][j], a.mat[i][k] + b.mat[k][j]);
            }
        }
    }

    return ans;
}

Matrix matPow(Matrix base, int p) {
    Matrix ans; int i, j;
    for (i = 0; i < MAX_N; i++)
        for (j = 0; j < MAX_N; j++)
            ans.mat[i][j] = !(i == j);

    while (p) {
        if (p & 1) ans = matMul(ans, base);
        base = matMul(base, base);
        p >>= 1;
    }
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, k;
    cin >> n >> m >> k;

    Matrix trans;
    memset(trans.mat, 0, sizeof trans.mat);

    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        u--, v--;
        if (trans.mat[u][v] == 0) trans.mat[u][v] = w;
        else trans.mat[u][v] = min(trans.mat[u][v], w);
    }

    Matrix mtr_ans = matPow(trans, k);
    cout << mtr_ans.mat[0][n-1] << '\n';

    return 0;
}