// https://leetcode.com/problems/shopping-offers/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> m_price, m_needs;
    vector<vector<int>> m_special;
    int n;
    const int INF = 1e9;
    int ans = INF;

    void solve(int idx, int cur_price, vector<int>& cur_trace) {
        if (cur_price > ans) return;
        for (int i=0; i<n; i++)
            if (cur_trace[i] > m_needs[i]) return;

        if (idx >= m_special.size()) {
            for (int i=0; i<n; i++) {
                if (cur_trace[i] != m_needs[i]) return;
            }
            ans = min(ans, cur_price);
            return;
        }

        // next idx
        solve(idx + 1, cur_price, cur_trace);

        // continue this idx
        for (int i=0; i<n; i++)
            cur_trace[i] += m_special[idx][i];
        cur_price += m_special[idx][n];
        solve(idx, cur_price, cur_trace);
        for (int i=0; i<n; i++)
            cur_trace[i] -= m_special[idx][i];
    }

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        n = price.size();

        m_price = price;
        m_special = special;
        m_needs = needs;

        for (int i=0; i<n; i++) {
            vector<int> tmp(n + 1, 0);
            tmp[i] = 1, tmp[n] = price[i];
            m_special.push_back(tmp);
        }

        vector<int> _(n, 0);
        solve(0, 0, _);

        return ans;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("ou.txt", "w", stdout);
    #endif

    vector<int> prices = {2, 3, 4};
    vector<vector<int>> special = {{1, 1, 0, 4}, {2, 2, 1, 9}};
    vector<int> needs = {1, 2, 1};

    Solution sol;
    int ans = sol.shoppingOffers(prices, special, needs);
    cout << ans << "\n";

    return 0;
}