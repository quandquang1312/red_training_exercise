// https://codeforces.com/contest/459/problem/D

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<vector<int>> tree;
    vector<int> lazy;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = { arr[start] };
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;
            build(arr, leftChild, start, mid);
            build(arr, rightChild, mid + 1, end);
            merge(tree[leftChild].begin(), tree[leftChild].end(),
                  tree[rightChild].begin(), tree[rightChild].end(),
                  back_inserter(tree[node]));
        }
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            for (int& val : tree[node]) {
                val += lazy[node];
            }
            if (start != end) {
                lazy[node * 2 + 1] += lazy[node];
                lazy[node * 2 + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    int query(int node, int start, int end, int l, int r, int x) {
        propagate(node, start, end);
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), x);
        }
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;
        return query(leftChild, start, mid, l, r, x) + query(rightChild, mid + 1, end, l, r, x);
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        propagate(node, start, end);
        if (r < start || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            lazy[node] += val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;
        updateRange(leftChild, start, mid, l, r, val);
        updateRange(rightChild, mid + 1, end, l, r, val);
        tree[node].clear();
        merge(tree[leftChild].begin(), tree[leftChild].end(),
              tree[rightChild].begin(), tree[rightChild].end(),
              back_inserter(tree[node]));
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    int query(int l, int r, int x) {
        return query(0, 0, n - 1, l, r, x);
    }

    void updateRange(int l, int r, int val) {
        updateRange(0, 0, n - 1, l, r, val);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);

    unordered_map<int, int> cnt;
    int trace2[n+1];
    vector<int> trace1(n+1);
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        cnt[arr[i]]++;
        trace1[i] = cnt[arr[i]];
    }

    for (int i=0; i<n; i++) {
        trace2[i] = cnt[arr[i]];
        cnt[arr[i]]--;
        if (cnt[arr[i]] == 0) cnt.erase(arr[i]);
    }

    cnt.clear();

    SegmentTree segTree(trace1);
    long long res = 0LL;
    for (int i=n-1; i>=0; i--)
    {
        int tmp = segTree.query(0, i-1, trace2[i]);
        res += tmp;
    }

    cout << res << endl;

    return 0;
}