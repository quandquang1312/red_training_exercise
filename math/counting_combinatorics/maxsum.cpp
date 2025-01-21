// https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const long long MOD = 1e9 + 7;

    long long binpow(long long a, long long b) {
        if (a == 0) return 0;
        if (b == 1) return a;

        long long res = 1;
        while (b) {
            if (b & 1) res = (res * a) % MOD;
            a = a * a % MOD;
            b >>= 1;
        }

        return res;
    }

    long long CnK(int n, int k) {
        if (k > n) return 0LL;
        if (k == n) return 1LL;

        k = min(k, n - k);

        long long numerator = 1, denominator = 1;
        for (int i=0; i<k; i++) {
            numerator = (numerator * (n - i) % MOD) % MOD;
            denominator = (denominator * (i + 1) % MOD) % MOD;
        }

        long long denominator_inv = binpow(denominator, MOD - 2);
        return (numerator * denominator_inv) % MOD;
    }

    int minMaxSums(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<vector<long long>> precal(n + 1, vector<long long>(k + 1, -1));

        for (int i=0; i<=n; i++) {
            precal[i][0] = 1;
            long long numerator = 1, denominator = 1;
            for (int j=0; j<min(k, i); j++) {
                numerator = (numerator * (i - j) % MOD) % MOD;
                denominator = (denominator * (j + 1) % MOD) % MOD;

                long long denominator_inv = binpow(denominator, MOD - 2);
                precal[i][j+1] = (numerator * denominator_inv) % MOD;
            }
        }

        long long ans = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<=k-1; j++) {
                if (j <= i) {
                    long long i_max = precal[i][j];
                    ans = (ans + (i_max * nums[i]) % MOD) % MOD;
                }

                if (j <= n - i - 1) {
                    long long i_min = precal[n - i - 1][j];
                    ans = (ans + (i_min * nums[i]) % MOD) % MOD;
                }
            }
        }

        return ans;
    }
};