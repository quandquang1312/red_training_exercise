#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree {
private:
    std::vector<int> tree;
    int n;

    void build(const std::vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
            return;
        }

        int mid = (start + end) / 2;
        build(nums, 2 * node, start, mid);
        build(nums, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] | tree[2 * node + 1];
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end)
            return 0;
        if (l <= start && r >= end)
            return tree[node];

        int mid = (start + end) / 2;
        int leftSum = query(2 * node, start, mid, l, r);
        int rightSum = query(2 * node + 1, mid + 1, end, l, r);
        return leftSum | rightSum;
    }

public:
    SegmentTree(const std::vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 1, n);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, k;
    cin >> n >> k;
    vector<int> arr(n+1);

    for (int i=1; i<=n; i++) cin >> arr[i];

    SegmentTree st(arr);

    int l = 1, r = n;
    int ans = 1e6;
    for (int i=1; i<=n; i++) {
        int l = i, r = n;
        while (l <= r && r <= n) {
            int m = (l + r) / 2;
            if (st.query(i, m) >= k) {
                ans = min(ans, m - i + 1);
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
    }

    cout << (ans == 1e6 ? -1 : ans) << endl;

    return 0;
}