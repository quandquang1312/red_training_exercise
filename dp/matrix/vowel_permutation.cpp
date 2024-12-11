// https://leetcode.com/problems/count-vowels-permutation/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const int MOD = 1e9 + 7;
    static const int N = 5;

    struct Matrix {
        vector<vector<long long>> mat;
        int n_rows, n_cols;

        Matrix(int n_rows, int n_cols, int val=0) : n_rows(n_rows), n_cols(n_cols) {
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

    int countVowelPermutation(int n) {
        // a e i o u
        vector<vector<int>> graph(N);

        graph[0].push_back(1); // a -> e
        graph[1].push_back(0); // e -> a
        graph[1].push_back(2); // e -> i
        
        // i not to another i
        for (int i=0; i<N; i++)
            if (i != 2) graph[2].push_back(i);

        graph[3].push_back(2); // o -> i
        graph[3].push_back(4); // o -> u
        graph[4].push_back(0); // u -> a

        Matrix trans(N, N, 0);
        for (int u=0; u<N; u++) {
            for (auto &v : graph[u]) {
                trans.setValue(u, v, 1);
            }
        }

        Matrix state(N, 1, 1);
        state = trans.pow(n-1) * state;

        int ans = 0;
        for (int i=0; i<N; i++) {
            ans += state.mat[i][0];
            ans %= MOD;
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("ou.txt", "w", stdout);
    #endif

    int N = 5;
    Solution sol;
    int ans = sol.countVowelPermutation(N);
    cout << ans << "\n";

    return 0;
}