// https://leetcode.com/problems/total-characters-in-string-after-transformations-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const int MOD = 1e9 + 7;
    static const int n = 26;

    struct Matrix {
        vector<vector<long long>> mat;
        int n_rows, n_cols;

        // Matrix(int n_rows, int n_cols) : n_rows(n_rows), n_cols(n_cols) {
        //     mat.resize(n_rows, vector<long long>(n_cols, 0));
        // }

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

    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        vector<vector<int>> adj(n + 1);
        for (int u=0; u<n; u++) {
            int spread = nums[u];
            for (int i=1; i<=spread; i++) {
                int v = (u + i) % n;
                adj[v].push_back(u);
            }
        }

        Matrix trans(n, n, 0);
        for (int u=0; u<n; u++) {
            for (auto &v : adj[u]) {
                trans.setValue(u, v, 1);
            }
        }

        Matrix state(n, 1, 0);
        int cnt[n] {};
        for (auto &c : s) {
            int idx = c - 'a';
            cnt[idx]++;
        }

        for (int i=0; i<n; i++) state.setValue(i, 0, cnt[i]);

        state = trans.pow(t) * state;

        int ans = 0;
        for (int i=0; i<n; i++) {
            ans += state.mat[i][0];
            ans %= MOD;
        }

        return ans;

        // vector<vector<int>> dp(n + 1, vector<int>(t + 1, 0));
        // for (auto &c : s) {
        //     int u = (c - 'a') % n;
        //     dp[u][0]++;
        // }

        // for (int i=1; i<=t; i++) {
        //     for (int u=0; u<n; u++) {
        //         for (auto &v : adj[u]) {
        //             dp[u][i] += dp[v][i - 1];
        //             dp[u][i] %= MOD;
        //         }
        //     }
        // }

        // int ans = 0;
        // for (int u=0; u<n; u++) {
        //     ans += dp[u][t];
        //     ans %= MOD;
        // }

        // return ans;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../ou.txt", "w", stdout);
    #endif

    string s = "abcyy";
    int t = 2;
    vector<int> nums = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2};

    Solution sol;
    int ans = sol.lengthAfterTransformations(s, t, nums);

    // Should be 8
    cout << ans << "\n";

    return 0;
}