// https://leetcode.com/problems/stone-game/description/?envType=problem-list-v2&envId=dynamic-programming

#include <bits/stdc++.h>
using namespace std;

#define int long long

class Solution {
public:
    vector<int> m_piles;
    int dp[2][505][505];
    int n, stones = 0;

    int solve(int player, int left, int right) {
        if (dp[player][left][right] != -1) return dp[player][left][right];

        if (left >= right) {
            return dp[player][left][right] = m_piles[left];
        }

        if (player == 0) { // alice
            int c_left  = m_piles[left]  + solve(1 - player, left + 1, right);
            int c_right = m_piles[right] + solve(1 - player, left, right - 1);
            return dp[player][left][right] = max(c_left, c_right);
        } else { // bob
            int c_left  = m_piles[left] +  solve(1 - player, left + 1, right);
            int c_right = m_piles[right] + solve(1 - player, left, right - 1);
            return dp[player][left][right] = min(c_left, c_right);
        }
    }

    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        m_piles = piles;

        memset(dp, -1, sizeof dp);

        for (int i=0; i<piles.size(); i++) stones += piles[i];

        int ans = solve(0, 0, n-1);
        if (ans > stones/2) return true;
        return false;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        // freopen("in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    // vector<int> piles = {5,3,4,5};
    vector<int> piles = {3,7,2,3};

    Solution sol;
    bool ans = sol.stoneGame(piles);
    cout << ans << "\n";

    return 0;
}