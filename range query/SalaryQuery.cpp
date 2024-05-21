// https://cses.fi/problemset/task/1144

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200100

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, q, mmax = -1; cin >> n >> q;
    int arr[n];

    vector<int> points;
    unordered_map<int, int> cnt;
    for (int i=0; i<n; i++) {
        cin >> arr[i]; 
        mmax = max(mmax, arr[i]);
        points.push_back(arr[i]);
        cnt[arr[i]]++;
    }

    unordered_map<int, int> coor;

    char type; int a, b;

    vector<tuple<char, int, int>> que;
    for (int i=0; i<q; i++) {
        cin >> type >> a >> b;
        points.push_back(a);
        points.push_back(b);
        que.push_back(make_tuple(type, a, b));
    }

    sort(points.begin(), points.end());
    points.erase(unique(points.begin(),points.end()), points.end());
    int sz = points.size();

    for (int i=0; i<sz; i++) coor[points[i]] = i;

    FenwickTree ft(sz+5);

    for (int i=0; i<n; i++) {
        ft.add(coor[arr[i]], 1);
    }

    for (int i=0; i<q; i++) {
        type = get<0>(que[i]);
        a = get<1>(que[i]), b = get<2>(que[i]);

        if (type == '?') {
            int ans = ft.query(coor[a], coor[b]);
            cout << ans << endl;
        } else {
            int val = arr[a-1];
            ft.add(coor[val], -1);
            ft.add(coor[b], 1);
            arr[a-1] = b;
        }
    }

    return 0;
}