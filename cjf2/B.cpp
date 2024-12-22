#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

#define LOG(...) print_with_dash(#__VA_ARGS__, __VA_ARGS__)

template<typename T>
void print_with_dash(const std::string& names, T value) {
    std::cout << names << ": " << value << std::endl;
}

template<typename T, typename... Args>
void print_with_dash(const std::string& names, T value, Args... args) {
    size_t pos = names.find(',');
    std::cout << names.substr(0, pos) << ": " << value << " - ";
    print_with_dash(names.substr(pos + 1), args...);
}

class SegmentTree { // 0-based segment tree with lazy
public:
    vector<int> tree, lazy;
    int n;

    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start] % MOD;
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;
            build(arr, leftChild, start, mid);
            build(arr, rightChild, mid + 1, end);
            tree[node] = (tree[leftChild] + tree[rightChild]) % MOD;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        if (lazy[node] != 0) {
            tree[node] = (tree[node] + (end - start + 1) * lazy[node]) % MOD;
            if (start != end) {
                lazy[2 * node + 1] = (lazy[2 * node + 1] + lazy[node]) % MOD;
                lazy[2 * node + 2] = (lazy[2 * node + 2] + lazy[node]) % MOD;
            }
            lazy[node] = 0;
        }

        if (start > r || end < l) {
            return;
        }

        if (start >= l && end <= r) {
            tree[node] = (tree[node] + (end - start + 1) * val) % MOD;
            if (start != end) {
                lazy[2 * node + 1] = (lazy[2 * node + 1] + val) % MOD;
                lazy[2 * node + 2] = (lazy[2 * node + 2] + val) % MOD;
            }
            return;
        }

        int mid = (start + end) / 2;
        updateRange(2 * node + 1, start, mid, l, r, val);
        updateRange(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = (tree[2 * node + 1] + tree[2 * node + 2]) % MOD;
    }

    int queryRange(int node, int start, int end, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] = (tree[node] + (end - start + 1) * lazy[node]) % MOD;
            if (start != end) {
                lazy[2 * node + 1] = (lazy[2 * node + 1] + lazy[node]) % MOD;
                lazy[2 * node + 2] = (lazy[2 * node + 2] + lazy[node]) % MOD;
            }
            lazy[node] = 0;
        }

        if (start > r || end < l) {
            return 0;
        }

        if (start >= l && end <= r) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int leftResult = queryRange(2 * node + 1, start, mid, l, r);
        int rightResult = queryRange(2 * node + 2, mid + 1, end, l, r);
        return (leftResult + rightResult) % MOD;
    }

    void updateRange(int l, int r, int val) {
        updateRange(0, 0, n - 1, l, r, val);
    }

    int query(int l, int r) {
        return queryRange(0, 0, n - 1, l, r);
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
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<int> arr(n);
        for (int i=0, d; i<n; i++) cin >> arr[i];

        vector<int> t(m), L(m), R(m);

        for (int i=0; i<m; i++) cin >> t[i];
        for (int i=0; i<m; i++) cin >> L[i];
        for (int i=0; i<m; i++) cin >> R[i];

        SegmentTree st(arr);

        int ori = 0, sign = 0;

        for (int i=0; i<m; i++) {
            if (t[i] == 1) {
                if (sign == 0) ori = (ori + L[i]) % n;
                else {
                    ori = ori - L[i];
                    if (ori < 0) ori = n + ori;
                }
            } else if (t[i] == 2) {
                if (sign == 1) ori = (ori + L[i]) % n;
                else {
                    ori = ori - L[i];
                    if (ori < 0) ori = n + ori;
                }
            } else if (t[i] == 3) {
                sign = 1 - sign;
            } else if (t[i] == 4) {
                if (sign == 0) {
                    if (ori + L[i] >= n) {
                        st.updateRange(ori, n-1, R[i]);
                        int rm = L[i] - ((n-1) - ori + 1);
                        st.updateRange(0, rm - 1, R[i]);
                    } else {
                        st.updateRange(ori, ori + L[i] - 1, R[i]);
                    }
                } else {
                    if (ori - L[i] >= 0) st.updateRange(ori - L[i] + 1, ori, R[i]);
                    else {
                        st.updateRange(0, ori, R[i]);
                        int tt = (n + (ori - L[i])) % n;
                        st.updateRange(tt + 1, n - 1, R[i]);
                    }
                }
            } else {
                int ans = 0;
                if (sign == 0) {
                    if (ori + L[i] >= n) {
                        ans = st.query(ori, n - 1);
                        int rm = L[i] - ((n-1) - ori + 1);
                        ans += st.query(0, rm - 1);
                        ans %= MOD;
                    } else {
                        ans = st.query(ori, ori + L[i] - 1);
                    }
                } else {
                    if (ori - L[i] >= 0) {
                        ans += st.query(ori - L[i] + 1, ori);
                    } else {
                        ans += st.query(0, ori);
                        ans %= MOD;
                        int tt = (n + (ori - L[i])) % n;
                        ans += st.query(tt + 1, n - 1);
                        ans %= MOD;
                    }
                }
                cout << ans << " ";
            }
        }

        cout << "\n";

    }

    return 0;
}