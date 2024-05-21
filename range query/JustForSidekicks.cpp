// https://open.kattis.com/contests/g4eg9w/problems/justforsidekicks

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200050
int gems[7], arr[MAXN];

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
    int n, q;
    cin >> n >> q;

    for (int i=1; i<=6; i++) cin >> gems[i];

    vector<FenwickTree> fts(7, FenwickTree(n+1));

    string str; cin >> str;
    for (int i=1; i<=n; i++) {
        arr[i] = str[i-1] - '0';
        fts[arr[i]].add(i, 1);
    }

    int type, a, b;
    while (q--) {
        cin >> type >> a >> b;
        if (type == 1) {
            fts[arr[a]].add(a, -1);
            fts[b].add(a, 1);
            arr[a] = b;
        } else if (type == 2) {
            gems[a] = b;
        } else { // type == 3
            int sm = 0;
            for (int i=1; i<=6; i++) {
                int fre = fts[i].query(a, b);
                sm += fre * gems[i];
            }

            cout << sm << endl;
        }
    }

    return 0;
}