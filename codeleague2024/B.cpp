#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;

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

long long calculate_Fn(long long n, int a, int b, int c, int d) {
    Matrix trans(4, 4);
    trans.mat = {
        {3, 2, 2, 3},
        {0, 1, 0, 2},
        {1, 0, 0, 0},
        {0, 1, 0, 0},
    };

    Matrix state(4, 1);
    state.mat = {{a}, {c}, {b}, {d}};

    state = trans.pow(n-1) * state;

    return state.mat[0][0];
}

int main() {
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    long long n;
    int a , b, c, d;
    cin >> a >> b >> c >> d >> n;

    // cout << "G_" << n << " is: " << calculate_Gn(n, c, d) << endl;
    // cout << "F_" << n << " is: " << calculate_Fn(n, a, b, c, d) << endl;
    cout << calculate_Fn(n, a, b, c, d) << endl;
    
    return 0;
}
