// https://leetcode.com/problems/house-robber-ii/description

#include <bits/stdc++.h>
using namespace std;

#define int long long

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return nums[0];
        else if (n == 2) return max(nums[0], nums[1]);
        else {
            int dp[110][2][2] {};

            dp[0][0][0] = 0;
            dp[0][1][1] = nums[0];

            for (int i=1; i<n; i++) {
                dp[i][0][0] = max(dp[i-1][0][0], dp[i-1][1][0]);
                dp[i][0][1] = max(dp[i-1][0][1], dp[i-1][1][1]);
                dp[i][1][0] = dp[i-1][0][0] + nums[i];
                if (i != n - 1)
                    dp[i][1][1] = dp[i-1][0][1] + nums[i];
            }

            return max(dp[n-1][1][0], max(dp[n-1][0][0], dp[n-1][0][1]));
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    

    return 0;
}