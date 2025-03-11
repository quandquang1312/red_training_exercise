// https://www.codechef.com/problems/MCO16404

#include <bits/stdc++.h>
using namespace std;

#define int long long

class Trie {
public:
    Trie* child[2];
    bool isLeaf;

    Trie() {
        isLeaf = false;

        for (int i=0; i<2; i++)
            child[i] = nullptr;
    }
    
    void insert(const int &num) {
        Trie* root = this;
        for (int i=31; i>=0; i--) {
            int bit = (num >> i) & 1;
            if (root->child[bit] == nullptr) {
                Trie* newTrie = new Trie();
                root->child[bit] = newTrie;
            }

            root = root->child[bit];
        }

        root->isLeaf = true;
    }
    
    bool search(const int &num) {
        Trie* root = this;
        if (root == nullptr) return false;

        for (int i=31; i>=0; i--) {
            int bit = (num >> i) & 1;
            if (root->child[bit] == nullptr) return false;
            root = root->child[bit];
        }

        return root->isLeaf;
    }
    
    int getMax(const int &num) {
        Trie* root = this;
        
        int maxNum = 0;
        
        for (int i=31; i>=0; i--) {
            int bit = (num >> i) & 1;
            if (root->child[1 ^ bit] != nullptr) {
                maxNum |= (1 << i);
                root = root->child[1 ^ bit];
            } else {
                root = root->child[bit];
            }
        }
        
        return maxNum;
    }
};

class SegmentTree {
private:
    int n;
    vector<Trie*> tree;

    Trie* merge(Trie* a, Trie* b) {
        if (!a && !b) return nullptr;
        if (!a) return b;
        if (!b) return a;

        Trie* newTrie = new Trie();
        newTrie->isLeaf = a->isLeaf | b->isLeaf;
        for (int i=0; i<2; i++) {
            newTrie->child[i] = merge(a->child[i], b->child[i]);
        }

        return newTrie;
    }

    void build(const vector<int>& arr, int node, int tl, int tr) {
        if (tl == tr) {
            tree[node] = new Trie();
            tree[node]->insert(arr[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(arr, node * 2, tl, tm);
            build(arr, node * 2 + 1, tm + 1, tr);
            tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
        }
    }

    void update(int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            if (tree[node] == nullptr) tree[node] = new Trie();
            tree[node]->insert(val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(node*2, tl, tm, pos, val);
            else
                update(node*2+1, tm+1, tr, pos, val);
            tree[node] = merge(tree[node*2], tree[node*2+1]);
        }
    }

    int query(int node, int tl, int tr, int l, int r, int x) {
        if (l > r) return 0;
        if (l == tl && r == tr) {
            return tree[node]->getMax(x);
        }
        int tm = (tl + tr) / 2;
        int maxLeft  = query(node*2, tl, tm, l, min(r, tm), x);
        int maxRight = query(node*2+1, tm+1, tr, max(l, tm+1), r, x);

        return max(maxLeft, maxRight);
    }

public:
    SegmentTree(int sz) : n(sz) {
        tree.assign(4 * n, nullptr);
    }

    void build(const vector<int> arr) {
        build(arr, 1, 1, n);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r, int x) {
        return query(1, 1, n, l, r, x);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<int> arr(n + 1);
    for (int i=1; i<=n; i++) {
        cin >> arr[i];
    }

    SegmentTree st(n + 1);
    st.build(arr);

    int q; cin >> q;

    int l, r, x;
    while (q--) {
        cin >> l >> r >> x;
        cout << st.query(l, r, x) << "\n";
    }

    return 0;
}