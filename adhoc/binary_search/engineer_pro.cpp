// https://leetcode.com/problems/find-k-th-smallest-pair-distance/

#include <bits/stdc++.h>
using namespace std;

#define int long long

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        auto check = [&] (int val) -> bool {
            int cnt = 0;

            // Binary Search
            // for (int i=0; i<n; i++) {
            //     int pos = upper_bound(nums.begin() + i + 1, nums.end(), nums[i] + val) - nums.begin();
            //     cnt += pos - i - 1;
            // }

            // Two pointer
            int r = 0;
            for (int i=0; i<n; i++) {
                while (nums[r] <= nums[i] + val && r < n) r++;

                cnt += r - i - 1;
                if (cnt >= k) return true;
            }


            return (cnt >= k);
        };

        int l = 0, r = nums[n - 1] - nums[0];
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }

        return l;
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