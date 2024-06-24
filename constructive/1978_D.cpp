// https://codeforces.com/contest/1978/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200010

class SegmentTree {
public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        this->arr = arr;
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    vector<int> getDecreasingSubarray(int i) {
        if (i + 1 >= n) {
            return {};
        }
        return query(0, 0, n - 1, i + 1, n - 1);
    }

private:
    int n;
    vector<int> arr;
    vector<vector<int>> tree;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {arr[start]};
        } else {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;
            build(left_child, start, mid);
            build(right_child, mid + 1, end);
            tree[node] = merge(tree[left_child], tree[right_child]);
        }
    }

    vector<int> merge(const vector<int>& left, const vector<int>& right) {
        vector<int> merged;
        int i = 0, j = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] > right[j]) {
                merged.push_back(left[i]);
                i++;
            } else {
                merged.push_back(right[j]);
                j++;
            }
        }
        while (i < left.size()) {
            merged.push_back(left[i]);
            i++;
        }
        while (j < right.size()) {
            merged.push_back(right[j]);
            j++;
        }
        return merged;
    }

    vector<int> query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return {};
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        vector<int> left_query = query(left_child, start, mid, l, r);
        vector<int> right_query = query(right_child, mid + 1, end, l, r);
        return merge(left_query, right_query);
    }
};


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--)
    {
        int n, c;
        cin >> n >> c;
        int arr[n+5] {}, presum[n+5] {};
        bool larger[n+5] {};

        vector<int> tmp(n);

        int first_max = -1, max_value = -1;
        for (int i=1; i<=n; i++) {
            cin >> arr[i];
            tmp[i-1] = arr[i];
            if (i == 1) arr[i] += c;
            presum[i] = presum[i-1] + arr[i];
            
            if (arr[i] > max_value) {
                first_max = i;
                max_value = arr[i];
                larger[i] = true;
            }
        }

        SegmentTree st(tmp);

        // for (int i=0; i<n; i++) {
        //     vector<int> sub = st.getDecreasingSubarray(i);
        //     cout << i << ": ";
        //     for (auto &e : sub) {
        //         cout << e << " ";
        //     }
        //     cout << endl;
        // }

        // continue;
        int cnt = 1;
        for (int i=1; i<=n; i++) {
            if (i == first_max) {
                cout << "0 ";
            } else {
                if (i - 1 == first_max) {
                    cout << cnt << " ";
                } else {
                    cout << cnt << " ";
                    cnt++;
                    // cnt++;
                }
                // cout << cnt << " ";
                // cnt++;
                continue;
                // if no element larger than i from 1->i-1,
                    // i should take all those elements
                    // if >= max_value -> ans is i - 1;
                    // else it should take all elements behind it
                    // one by one from the largest until it become
                    // the largest
                if (larger[i] == false)
                {
                    if (arr[i] + presum[i-1] >= max_value) {
                        cout << i - 1 << " ";
                    } else {
                        vector<int> sub = st.getDecreasingSubarray(i-1);
                        int tmp = arr[i] + presum[i-1], j = 0;
                        for (; j<sub.size() && tmp < sub[j]; j++) {
                            tmp += sub[j];
                        }

                        cout << (i - 1 + j) << " ";
                    }
                } else {
                    // if there's some element larger than i from 1->i-1
                        // i shoult take it one by one from the largest
                        // until it become larger than any element left yet
                    vector<int> sub = st.getDecreasingSubarray(i-1);
                    int current_max_value = sub[0];

                    int tmp = arr[i] + presum[i-1], j = 0;
                    if (tmp >= current_max_value) {
                        cout << i - 1 << " ";
                    } else {
                        for (; j<sub.size() && tmp < sub[j]; j++) {
                            tmp += sub[j];
                        }
                        cout << (i - 1 + j) << " ";
                    }
                }
            }
        }

        cout << endl;
    }

    return 0;
}