// https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/description/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 
class Solution {
private:
    vector<vector<long long>> adj;
    vector<long long> dp, arr;
    long long timer = 1;
    long long ans = -1, sm = 0;
    const long long MOD = 1e9 + 7;

    long long dfs(int u, int par) {
        if (dp[u] != -1) return dp[u];

        long long u_ans = arr[u];
        for (auto &v : adj[u]) {
            if (v == par) continue;
            int v_ans = dfs(v, u);
            u_ans = (u_ans + v_ans);
        }

        return dp[u] = u_ans;
    }

    void rerooting(int u, int par) {
        for (auto &v : adj[u]) {
            if (v == par) continue;
            long long original_u = dp[u], original_v = dp[v];

            // detach v from u
            dp[u] = (dp[u] - dp[v]);

            ans = max(ans, dp[u] * dp[v]);

            // attach u to v
            dp[v] = (dp[v] + dp[u]);

            rerooting(v, u);

            // backtrack
            dp[u] = original_u;
            dp[v] = original_v;
        }
    }

    void traverse(TreeNode* current) {
        long long u = current->val, cur_timer = timer;
        sm = (sm + u);
        arr[cur_timer] = u;

        if (current->left != nullptr) {
            timer++;
            adj[cur_timer].push_back(timer);
            adj[timer].push_back(cur_timer);
            traverse(current->left);
        }

        if (current->right != nullptr) {
            timer++;
            adj[cur_timer].push_back(timer);
            adj[timer].push_back(cur_timer);
            traverse(current->right);
        }
    }

public:
    int maxProduct(TreeNode* root) {
        adj.resize(50005);
        dp.resize(50005, -1);
        arr.resize(50005);

        traverse(root);

        dfs(1, 0);
        rerooting(1, 0);

        return ans % MOD;
    }
};