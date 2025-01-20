// https://codeforces.com/gym/102644/problem/B

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

long long calculate_Fn(long long n) {
    Matrix trans(2, 2);
    trans.mat = {{19, 6}, {7, 20}};

    Matrix state(2, 1);
    state.mat = {{1}, {0}};

    state = trans.pow(n) * state;

    return state.mat[0][0];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    // int othrs = 26 - 3 - 5, vowels = 5, sad = 2, hpp = 1;
    // vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    // dp[0][0] = 1;
    // for (int i=1; i<=n; i++) {
    //     dp[i][0] = (dp[i][0] + (dp[i-1][0] * (othrs + hpp)) % MOD) % MOD;
    //     dp[i][0] = (dp[i][0] + (dp[i-1][1] * (vowels + hpp)) % MOD) % MOD;
    //     dp[i][1] = (dp[i][1] + (dp[i-1][0] * (vowels + sad)) % MOD) % MOD;
    //     dp[i][1] = (dp[i][1] + (dp[i-1][1] * (othrs + sad)) % MOD) % MOD; 
    // }

    int ans = calculate_Fn(n);
    cout << ans << "\n";
    // cout << dp[n][0] << " - " << ans << "\n";

    return 0;
}