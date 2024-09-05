// https://cses.fi/problemset/task/1139

#include <bits/stdc++.h>
using namespace std;

vector<int> startIdx, endIdx, colors, acolors, ans;
int n, timer, max_st, max_en;
vector<vector<int>> adj;

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

void euler_tour(int at, int prev) {
    acolors[timer] = colors[at];
    startIdx[at] = timer++;
    max_st = max(max_st, timer);
    for (int n : adj[at]) {
        if (n != prev) { euler_tour(n, at); }
    }
    endIdx[at] = timer;
    max_en = max(max_en, timer);
}

void preprocess(int n) {
    colors.resize(n + 1);
    adj.resize(n + 1);
    startIdx.resize(n + 1);
    endIdx.resize(n + 1);
    ans.resize(n + 1);
    acolors.resize(n * 10);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cin >> n;
    preprocess(n);

    for (int i=1; i<=n; i++) cin >> colors[i];
    for (int i=0, u, v; i<n-1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    euler_tour(1, 0);

    vector<vector<pair<int, int>>> queries(max_st + 10);
    for (int i=1; i<=n; i++) {
        queries[startIdx[i]].push_back({i, endIdx[i]});
    }

    FenwickTree ft(max_en + 10);
    unordered_map<int, int> lst_idx;
    for (int i=max_en; i>=0; i--) {
        if (lst_idx.count(acolors[i]) > 0) ft.add(lst_idx[acolors[i]], -1);

        lst_idx[acolors[i]] = i;
        ft.add(i, 1);
        for (auto &[idx, en] : queries[i]) {
            ans[idx] = ft.query(i, en - 1);
        }
    }

    for (int i=1; i<=n; i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';

    return 0;
}