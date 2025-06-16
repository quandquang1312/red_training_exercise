// https://vjudge.net/problem/UVA-12299

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int merge(int a, int b) {
        return min(a, b);
    }

    void build(int node, int tl, int tr, const vector<int>& arr) {
        if (tl == tr) {
            tree[node] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(node*2, tl, tm, arr);
            build(node*2+1, tm+1, tr, arr);
            tree[node] = merge(tree[node*2], tree[node*2+1]);
        }
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[node] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node*2, tl, tm, pos, val);
            else
                update(node*2+1, tm+1, tr, pos, val);
            tree[node] = merge(tree[node*2], tree[node*2+1]);
        }
    }

    int query(int node, int tl, int tr, int l, int r) {
        if (l > r) return INT_MAX;
        if (l == tl && r == tr) {
            return tree[node];
        }
        int tm = (tl + tr) / 2;
        return merge(query(node*2, tl, tm, l, min(r, tm)),
                     query(node*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    SegmentTree(int sz) : n(sz) {
        tree.assign(4 * n, 0);
    }

    SegmentTree(const vector<int>& arr) : n(arr.size() - 1) {
        tree.assign(4 * n, INT_MAX);
        build(1, 1, n, arr);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<int> arr(n + 1);

    for (int i=1; i<=n; i++) cin >> arr[i];
    SegmentTree st(arr);

    while (q--) {
        string s; cin >> s;
        auto lpar = s.find('('), rpar = s.find(')');
        string inside = s.substr(lpar + 1, rpar - lpar - 1);
    
        if (s[0] == 'q') {
            auto comma = inside.find(',');
            int l = stoi(inside.substr(0, comma));
            int r = stoi(inside.substr(comma + 1));
            cout << st.query(l, r) << "\n";
        } 
        else { // s[0] = 's'
            vector<int> shift;
            size_t start = 0;
            while (start < inside.size()) {
                auto comma = inside.find(',', start);
                if (comma == string::npos) comma = inside.size();
                shift.push_back(stoi(inside.substr(start, comma - start)));
                start = comma + 1;
            }

            int first = arr[shift[0]];
            for (int i = 0; i < (int)shift.size() - 1; ++i) {
                int pos = shift[i], nxt = shift[i + 1];
                arr[pos] = arr[nxt];
                st.update(pos, arr[pos]);
            }
            int last = shift.back();
            arr[last] = first;
            st.update(last, first);
        }
    }

    return 0;
}