// https://leetcode.com/problems/non-overlapping-intervals/?envType=problem-list-v2&envId=dynamic-programming

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<int> dp;

    int find_lb(vector<vector<int>>& intervals, int val) {
        int l = 0, r = intervals.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (intervals[m][0] < val) l = m + 1;
            else r = m;
        }

        return l;
    }

    int solve(int idx, vector<vector<int>>& intervals) {
        // base-case idx = n
        if (idx == n) return 0;

        if (dp[idx] != -1) return dp[idx];
        
        // remove
        int rm = 1 + solve(idx + 1, intervals);
    
        // keep
        int pos = find_lb(intervals, intervals[idx][1]);
        int kp = (pos - idx - 1) + solve(pos, intervals);

        return dp[idx] = min(rm, kp);
    }

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        n = intervals.size();
        dp.assign(n + 1, -1);

        sort(intervals.begin(), intervals.end(), [] (vector<int>& v1, vector<int>& v2) {
            return v1[0] < v2[0]; 
        });

        int ans = solve(0, intervals);

        return ans;
    }
};