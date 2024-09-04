// https://cses.fi/problemset/task/1138

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<int> arr, startIdx, endIdx;
int timer;

class FenwickTree {
public:
    FenwickTree(int n) {
        this->n = n;
        ft.assign(n, 0);
    }

    FenwickTree(vector<int> arr) : FenwickTree(arr.size()) {
        for (int i=0; i<arr.size(); i++)
            add(i, arr[i]);
    }

    int query(int l, int r) {
        return sum(r) - sum(l-1);
    }

    void add(int idx, int vl) {
        for (; idx < n; idx = idx | (idx + 1))
            ft[idx] += vl;
    }

private:
    vector<int> ft;
    int n;

private:
    int g(int i) { return i & (i + 1); }
    int sum(int i) {
        int rs = 0;
        while (i >= 0) {
            rs += ft[i];
            i = g(i) - 1;
        }
        return rs;
    }
};

void preprocess(int n) {
    arr.resize(n + 1);
    startIdx.resize(n + 1);
    endIdx.resize(n + 1);
    adj.resize(n + 1);
}

void euler_tour(int at, int prev) {
    startIdx[at] = timer++;
    for (int n : adj[at]) {
        if (n != prev) { euler_tour(n, at); }
    }
    endIdx[at] = timer;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;

    preprocess(n);
    FenwickTree ft(n + 5);

    for (int i=1; i<=n; i++) cin >> arr[i];

    for (int i=1, u, v; i<n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    euler_tour(1, 0);
    for (int i=1; i<=n; i++) {
        ft.add(startIdx[i], arr[i]);
        ft.add(endIdx[i], -arr[i]);
    }

    int t, x, s;
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> s >> x;
            ft.add(startIdx[s], x - arr[s]);
            ft.add(endIdx[s], -(x - arr[s]));
            arr[s] = x;
        } else {
            cin >> s;
            int ans = ft.query(0, startIdx[s]);
            cout << ans << '\n';
        }
    }

    return 0;
}