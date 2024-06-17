#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 1000050

class SegmentTree
{
private:
    vector<vector<int>> tree;
    vector<bool> lazy;

    int n;

    void build(int node, int start, int end, const vector<int> &data)
    {
        if (start == end)
        {
            tree[node] = {data[start]};
        }
        else
        {
            int mid = (start + end) >> 1;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;

            build(left_child, start, mid, data);
            build(right_child, mid + 1, end, data);

            merge(tree[left_child].begin(), tree[left_child].end(),
                  tree[right_child].begin(), tree[right_child].end(),
                  back_inserter(tree[node]));
        }
    }

    void push(int node, int start, int end)
    {
        if (lazy[node])
        {
            sort(tree[node].begin(), tree[node].end());
            if (start != end)
            {
                int left_child = 2 * node + 1;
                int right_child = 2 * node + 2;
                lazy[left_child] = true;
                lazy[right_child] = true;
            }
            lazy[node] = false;
        }
    }

    void updateRange(int node, int start, int end, int l, int r)
    {
        push(node, start, end);

        if (start > end || start < r || end < l)
            return;

        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        if (start >= l && end <= r)
        {
            sort(tree[node].begin(), tree[node].end());

            if (start != end)
            {
                lazy[left_child] = true;
                lazy[right_child] = true;
            }
            return;
        }

        int mid = (start + end) >> 1;
        updateRange(left_child, start, mid, l, r);
        updateRange(right_child, mid + 1, end, l, r);
        merge(tree[left_child].begin(), tree[right_child].end(),
              tree[right_child].begin(), tree[right_child].end(),
              tree[node].begin());
    }

    int query(int node, int start, int end, int idx)
    {
        push(node, start, end);

        if (start == end)
        {
            return tree[node][0];
        }

        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        if (idx <= mid)
        {
            return query(left_child, start, mid, idx);
        }
        else
        {
            return query(right_child, mid + 1, end, idx);
        }
    }

public:
    SegmentTree(const vector<int> &data)
    {
        n = data.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, false);
        build(0, 0, n - 1, data);
    }

    void update(int l, int r)
    {
        updateRange(0, 0, n - 1, l, r);
    }

    int query(int idx)
    {
        return query(0, 0, n - 1, idx);
    }
};

int32_t main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    int n, q, k;
    cin >> n >> q >> k;

    vector<int> arr(n);

    for (auto &e : arr)
        cin >> e;

    SegmentTree segTree(arr);

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        segTree.update(l, r);
    }

    cout << segTree.query(k + 1) << endl;
    return 0;
}