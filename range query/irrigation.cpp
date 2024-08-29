// https://codeforces.com/contest/1181/problem/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

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

    int m, n, q;
    cin >> m >> n >> q;

    vector<int> arr(n);
    vector<pair<int, int>> city;

    for (int i=1; i<n; i++) {

    }

    int max_e = 0;
    FenwickTree ft(m + 5);

    unordered_map<int, int> mp;
    for (int i=0; i<m; i++) {
        cin >> arr[i];
        mp[arr[i]]++;
        max_e = max(max_e, mp[arr[i]]);
        ft.add(mp[arr[i]], 1);
    }

    for (int i=1; i<=n; i++) {
        if (mp.find(i) == mp.end()) mp[i] = 0;
    }

    for (auto &e : mp) {
        city.push_back({e.first, e.second});
    }

    sort(city.begin(), city.end(), [](pair<int, int> p1, pair<int, int> p2) {
        if (p1.second == p2.second)
            return p1.first < p2.first;
        return p1.second < p2.second;
    });

    for (int i=0; i<n; i++) {
        cout << city[i].first << "-" << city[i].second << '\n';
    }

    int total = 0;
    for (int i=1; i<=max_e; i++) {
        total += (n - ft.query(i, i));
        cout << i << "-> " << ft.query(i,i) << "\n";
    }

    cout << "total: " << total << '\n';

    auto solve = [&](int year) -> int {
        if (year > n * max_e) {
            int rs = (year % n);
            rs = rs + (rs == 0 ? n : 0);
            return rs;
        }

        year -= m;

        // cout << "year: " << year << '\n';
        int row = -1;
        for (int l=1; l<=max_e; l++) {
            int val = (n * l) - ft.query(0, l);
            // cout << l << ": " << val << '\n';
            if (val >= year) {
                row = l;
                break;
                // return l;
            }
        }

        int pos = year - (n * (row - 1) - ft.query(0, row - 1));
        // int new_pos = pos - 
        // return n - pos + 1;
        // return n - (ft.query(row, row) + pos) + 1;
        if (row == 1) return pos;
        else return 
        return pos;
    };

    for (int i=0; i<q; i++) {
        int x; cin >> x;
        cout << x << ": " << solve(x) << '\n';
        // cout << x << ": " << city[solve(x) - 1].first << "\n";
    }

    return 0;
}