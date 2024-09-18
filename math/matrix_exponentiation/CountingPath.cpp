// https://cses.fi/problemset/task/1723
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

struct Matrix {
    vector<vector<long long>> mat;
    int n_rows, n_cols;

    Matrix(int n_rows, int n_cols) : n_rows(n_rows), n_cols(n_cols) {
        mat.resize(n_rows, vector<long long>(n_cols, 0));
    }

    Matrix(int n_rows, int n_cols, int val) : n_rows(n_rows), n_cols(n_cols) {
        mat.resize(n_rows, vector<long long>(n_cols, val));
    }

    void setValue(int r, int c, int val) {
        mat[r][c] = val;
    }

    void print() {
        int n = n_rows, m = n_cols;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                cout << mat[i][j] << " ";
            }
            cout << "\n";
        }
    }

    static Matrix identity_matrix(int n) {
        Matrix I(n, n);
        for (int i = 0; i < n; i++) {
            I.mat[i][i] = 1;
        }
        return I;
    }

    Matrix operator*(const Matrix &other) const {
        int n = n_rows, m = other.n_cols;
        Matrix result(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < n_cols; k++) {
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
                    result.mat[i][j] %= MOD;
                }
            }
        }
        return result;
    }

    Matrix pow(long long power) const {
        Matrix result = identity_matrix(n_rows);
        Matrix base = *this;
        while (power > 0) {
            if (power & 1) {
                result = result * base;
            }
            base = base * base;
            power >>= 1;
        }
        return result;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, k;
    cin >> n >> m >> k;

    // Counting path is simple exponentiate the adjacency matrix
    vector<vector<int>> adj(n + 1);
    Matrix trans(n, n);
    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        u--, v--;
        trans.mat[u][v]++;
    }

    int mtr_ans = trans.pow(k).mat[0][n-1];

    #ifdef DEBUG
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        dp[1][0] = 1;

        for (int i=1; i<=k; i++) {
            for (int u=1; u<=n; u++) {
                for (auto &v : adj[u]) {
                    dp[u][i] += dp[v][i - 1];
                    dp[u][i] %= MOD;
                }
            }
        }

        int ans = dp[n][k];
        cout << "DEBUG: " << ans << endl;
    #endif

    cout << mtr_ans << '\n';

    return 0;
}