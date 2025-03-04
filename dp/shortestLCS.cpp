// https://leetcode.com/problems/shortest-common-supersequence/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        // trace solution of LCS
        auto LCS = [] (const string &a, const string &b) {
            int n = a.size(), m = b.size();
            vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
            for (int i=1; i<=n; i++) {
                for (int j=1; j<=m; j++) {
                    if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
                    else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }

            int i = n, j = m;
            string lcs;

            while (i > 0 && j > 0) {
                if (a[i - 1] == b[j - 1]) {
                    lcs.push_back(a[i - 1]);
                    i--; j--;
                } else {
                    if (dp[i - 1][j] > dp[i][j - 1]) i--;
                    else j--;
                }
            }

            reverse(lcs.begin(), lcs.end());
            return lcs;
        };

        int n = str1.size(), m = str2.size();

        string lcs = LCS(str1, str2);
        string ans = "";

        int j = 0, k = 0;
        for (int i=0; i<lcs.size(); i++) {
            while (j < n && str1[j] != lcs[i]) ans.push_back(str1[j++]);
            while (k < m && str2[k] != lcs[i]) ans.push_back(str2[k++]);

            ans.push_back(lcs[i]);
            j++, k++;
        }

        while (j < n) ans.push_back(str1[j++]);
        while (k < m) ans.push_back(str2[k++]);
        
        return ans;
    }
};