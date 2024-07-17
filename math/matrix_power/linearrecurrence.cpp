// https://open.kattis.com/problems/linearrecurrence?tab=metadata
#include <bits/stdc++.h>
using namespace std;

#define int long long
int MOD = 1e9 + 7;

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

    void print() {
        for (int i=0; i<mat.size(); i++) {
            for (int j=0; j<mat[0].size(); j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n;
    n++;
    int arr[n], x[n-1];
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = n-2; i >= 0; i--) cin >> x[i];

    Matrix trans(n, n);
    Matrix state(n, 1);

    for (int j = 0; j < n; j++) {
        trans.mat[1][j] = arr[j];
    }

    trans.mat[0][0] = 1;
    for (int i = 2; i < n; i++) {
        trans.mat[i][i-1] = 1;
    }

    state.mat[0][0] = 1;
    for (int i = 1; i < n; i++) state.mat[i][0] = x[i-1];

    cin >> q;
    while (q--) {
        int t;
        cin >> t >> MOD;

        Matrix ans = trans.pow(t) * state;
        // ans.print();
        cout << ans.mat[n-1][0] << endl;
    }

    return 0;
}
