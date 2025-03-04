// https://atcoder.jp/contests/abc369/tasks/abc369_f

#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree {
private:
    int n;
    vector<pair<int, int>> tree;

    pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
        int val = max(a.first, b.first);
        int idx = (a.first > b.first ? a.second : b.second);
        return {val, idx};
    }

    void update(int node, int tl, int tr, int pos, int val, int row) {
        if (tl == tr) {
            tree[node] = {val, row};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node*2, tl, tm, pos, val, row);
            else
                update(node*2+1, tm+1, tr, pos, val, row);
            tree[node] = merge(tree[node*2], tree[node*2+1]);
        }
    }

    pair<int, int> query(int node, int tl, int tr, int l, int r) {
        if (l > r) return {0, -1};
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node*2, tl, tm, l, min(r, tm)),
               query(node*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(int sz) : n(sz) {
        tree.assign(4 * n, {0, -1});
    }

    void update(int pos, int val, int row) {
        update(1, 1, n, pos, val, row);
    }

    pair<int, int> query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int h, w, n;
    cin >> h >> w >> n;

    vector<pair<int, int>> points(n);

    for (int i=0; i<n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    auto cmp = [] (const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.first == p2.first) return p1.second < p2.second;
        return p1.first < p2.first;
    }; 

    sort(points.begin(), points.end(), cmp);

    int add = 0;

    if (!(points.back().first == h && points.back().second == w)) add++, points.push_back({h, w});
    if (!(points[0].first == 1 && points.back().second == 1)) add++, points.push_back({1, 1});

    sort(points.begin(), points.end(), cmp);

    n = points.size();

    SegmentTree st(w + 1);
    vector<int> dp(n, 0), trace(n, -1);

    for (int i=0; i<n; i++) {
        auto [x, y] = points[i];
        auto [prev_max, idx] = st.query(1, y);

        trace[i] = idx;

        dp[i] = prev_max + 1;

        st.update(y, max(dp[i], prev_max), i);
    }

    cout << dp[n - 1] - add << "\n"; 
    string rs = "";
    
    vector<pair<int, int>> seq;
    for (int i=n-1; i!=-1; i=trace[i]) {
        seq.push_back(points[i]);
    }

    if (!(seq.back().first == 1 && seq.back().second == 1)) seq.push_back({1, 1});
    reverse(seq.begin(), seq.end());

    for (int i=0; i<seq.size()-1; i++) {
        int d = seq[i + 1].first - seq[i].first;
        int r = seq[i + 1].second - seq[i].second;

        while (d--) rs.push_back('D');
        while (r--) rs.push_back('R');
    }

    cout << rs << "\n";

    return 0;
}