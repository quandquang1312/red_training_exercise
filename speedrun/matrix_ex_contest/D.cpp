// https://codeforces.com/gym/102644/problem/D

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

    vector<vector<int>> adj(n + 1);
    Matrix trans(n, n);
    for (int i=0, u, v; i<m; i++) {
        cin >> u >> v;
        adj[v].push_back(u);
    }

    for (int u=1; u<=n; u++) {
        for (auto &v : adj[u]) {
            trans.setValue(u - 1, v - 1, 1);
        }
    }

    Matrix state(n, 1, 1);
    state = trans.pow(k) * state;

    int mtr_ans = 0;
    for (int i=0; i<n; i++) {
        mtr_ans += state.mat[i][0];
        mtr_ans %= MOD;
    }

    #ifdef DEBUG
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        for (int u=1; u<=n; u++) dp[u][0] = 1;

        for (int i=1; i<=k; i++) {
            for (int u=1; u<=n; u++) {
                for (auto &v : adj[u]) {
                    dp[u][i] += dp[v][i - 1];
                    dp[u][i] %= MOD;
                }
            }
        }

        int ans = 0;
        for (int u=1; u<=n; u++) {
            ans += dp[u][k];
            ans %= MOD;
        }

        cout << "debug: " << ans << endl;
    #endif

    cout << mtr_ans << '\n';

    return 0;
}