// https://cses.fi/problemset/task/1722

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

long long calculate_Gn(long long n, int c, int d) {
    Matrix trans(2, 2);
    trans.mat = {{1, 2}, {1, 0}};

    Matrix state(2, 1);
    state.mat = {{c}, {d}};

    state = trans.pow(n - 1) * state;

    return state.mat[0][0];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    Matrix base(2,2);
    base.mat = {{1, 1}, {1, 0}};

    int n; cin >> n;

    Matrix state(2,1);
    state.mat = {{1}, {0}};

    state = base.pow(n - 1) * state;

    cout << (state.mat[0][0]) << '\n';

    return 0;
}