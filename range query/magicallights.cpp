// https://open.kattis.com/problems/magicallights

#include <bits/stdc++.h>
using namespace std;

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

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);

    int n, q; cin >> n >> q;
    adj.resize(n+1);
    startIdx.resize(n+1), endIdx.resize(n+1);

    vector<FenwickTree> fts(101, FenwickTree(n+1));

    vector<int> colours(n+1);
    for (int i=1; i<=n; i++) cin >> colours[i];

    for (int i=2; i<=n; i++)
    {
        int parent; cin >> parent;
        adj[parent].push_back(i);
        adj[i].push_back(parent);
    }
    euler_tour(1, 0);

    // for (int i=1; i<=n; i++) {
    //     printf("%d: start: %d, end: %d\n", i, startIdx[i], endIdx[i]);
    // }

    for (int i=1; i<=n; i++) {
        fts[colours[i]].add(startIdx[i], 1);
    }

    int k, x;
    while (q--)
    {
        cin >> k >> x;
        if (k == 0) {
            int ans = 0;
            int st = startIdx[x], en = endIdx[x] - 1;
            for (int i=1; i<=100; i++) {
                ans += (fts[i].query(st, en) % 2 != 0);
                // ans += fts[i].query(st, en);
            }
            cout << ans << endl;
            // printf("%d: %d\n", k, ans);
        } else {
            int st = startIdx[x], en = endIdx[x] - 1;
            int curr_color = colours[x];
            fts[curr_color].add(st, -1);
            fts[k].add(st,1);
            colours[x] = k;
        }
    }

    return 0;
}