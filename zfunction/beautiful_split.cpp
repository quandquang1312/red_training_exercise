// https://leetcode.com/problems/count-beautiful-splits-in-an-array/description/

#include <bits/stdc++.h>
using namespace std;

#define int long long


class Solution {
public:
    vector<int> zfunction(const vector<int>& nums) {
        int n = nums.size();

        vector<int> z(n, 0);
        int l = 0, r = 0;

        for (int i=0; i<n; i++) {
            if (i <= r) z[i] = min(r - i + 1, z[i - l]);
            
            while (i + z[i] < n && nums[z[i]] == nums[i + z[i]]) z[i]++;

            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }

        return z;
    }

    int beautifulSplits(vector<int>& nums) {
        int n = nums.size();
        vector<int> index_freq[51];

        for (int i=0; i<n; i++) {
            index_freq[nums[i]].push_back(i);
        }

        int ans = 0;
        set<int> j_of_0;
        for (int num=0; num<=50; num++) {
            if (index_freq[num].size() <= 1) continue;
            auto &v = index_freq[num];
            auto i_iter = v.begin();
            if (num == nums[0] && ans > 0) continue;
            for (; i_iter!=v.end(); i_iter++) {
                int i = *i_iter;
                auto it = std::next(i_iter);
                int dist_it = it - i_iter;
                int dist_j  = v.end() - it;

                for (; it != v.end(); ++it) {
                    int j = *it;

                    if (j_of_0.find(i) != j_of_0.end()) continue;

                    if ((n - j >= j - i) && (dist_it <= dist_j)) {
                        int k = 1;
                        bool flag = true;
                        while (i + k < j && j + k < n) {
                            if (nums[i + k] != nums[j + k]) {
                                flag = false;
                                break;
                            };
                            k++;
                        }

                        if (flag) {
                            if (i == 0) {
                                ans += n - (j + k);
                                j_of_0.insert(j);
                            } else {
                                if (j_of_0.find(i) == j_of_0.end()) ans++;
                            }
                        }
                    } 
                    // else break;

                    dist_it++;
                    dist_j--;
                }
            }
        }

        return ans;
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