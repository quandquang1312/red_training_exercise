// https://codeforces.com/gym/102644/problem/A

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Matrix {
    vector<vector<double>> mat;
    int n_rows, n_cols;

    Matrix(int n_rows, int n_cols) : n_rows(n_rows), n_cols(n_cols) {
        mat.resize(n_rows, vector<double>(n_cols, 0));
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

double calculate_Fn(int n, double p) {
    Matrix trans(2, 2);
    trans.mat = {{1 - p, p}, {p, 1 - p}};

    Matrix state(2, 1);
    state.mat = {{1 - p}, {p}};

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

    int n; double p; cin >> n >> p;

    // brute force
    // vector<vector<double>> dp(n + 1, vector<double>(2, 0.0));
    // dp[1][0] = 1.0 - p, dp[1][1] = p;
    // for (int i=2; i<=n; i++) {
    //     dp[i][0] = (dp[i-1][0] * (1.0 - p)) + (dp[i-1][1] * p);
    //     dp[i][1] = (dp[i-1][0] * p) + (dp[i-1][1] * (1.0 - p));
    // }

    double ans = calculate_Fn(n, p);
    printf("%.9f\n", ans);

    return 0;
}