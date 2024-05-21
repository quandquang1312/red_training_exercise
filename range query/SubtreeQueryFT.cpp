// https://cses.fi/problemset/task/1137/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200050

int arr[MAXN];
vector<vector<int>> adj;
vector<int> startIdx, endIdx;
int timer = 0;

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
    startIdx[at] = timer++;
    for (int n : adj[at]) {
        if (n != prev) { euler_tour(n, at); }
    }
    endIdx[at] = timer;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);

    int n, q; cin >> n >> q;
    for (int i=1; i<=n; i++) cin >> arr[i];

    adj.resize(n+1);
    startIdx.resize(n+1), endIdx.resize(n+1);

    for (int i=1; i<=n-1; i++) {
        int src, dst;
        cin >> src >> dst;
        adj[src].push_back(dst);
        adj[dst].push_back(src);
    }

    euler_tour(1, 0);

    FenwickTree ft(n+1);

    for (int i=1; i<=n; i++) {
        ft.add(startIdx[i], arr[i]);
    }

    int type, s, x;
    while (q--) {
        cin >> type;
        if (type == 1) {
            cin >> s >> x;
            int curr_value = ft.query(startIdx[s], startIdx[s]);
            ft.add(startIdx[s], -curr_value);
            ft.add(startIdx[s], x);
        } else {
            cin >> s;
            int ans = ft.query(startIdx[s], endIdx[s] - 1);
            cout << ans << endl;
        }
    }

    return 0;
}