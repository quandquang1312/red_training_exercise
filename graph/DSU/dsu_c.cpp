// https://oj.vnoi.info/problem/dsu_c

#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
    vector<int> p, rank, setSize;
    vector<int> maxIn, minIn;
    vector<vector<int>> childs;
    vector<int> value;
    int numSets;
    bool m_child;

public:
    DSU(int n, bool needChild) {
        m_child = needChild;
        p.assign(n, 0);
        for (int i=0; i<n; i++) p[i] = i;

        rank.assign(n, 0);
        setSize.assign(n, 1);
        maxIn.assign(n, 0);
        minIn.assign(n, 1e9);
        value.assign(n, 0);

        if (m_child) {
            childs.resize(n);
            for (int i=0; i<n; i++) {
                childs[i].push_back(i);
            }
        }

        iota(maxIn.begin(), maxIn.end(), 0);
        iota(minIn.begin(), minIn.end(), 0);

        numSets = n;
    }

    int findSet(int i) {
        if (p[i] == i) return i;
        return p[i] = findSet(p[i]);
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    int sizeOfSet(int i) {
        return setSize[findSet(i)];
    }

    int numOfSets() {
        return numSets;
    }

    int getMax(int i) {
        return maxIn[findSet(i)];
    }

    int getMin(int i) {
        return minIn[findSet(i)];
    }

    void addValue(int i, int val) {
        int x = findSet(i);
        for (auto &e : childs[x]) {
            value[e] += val;
        }
    }

    int getValue(int i) {
        return value[i];
    }

    void unionSet(int i, int j) {
        int x = findSet(i);
        int y = findSet(j);

        if (x == y) return;

        if (rank[x] > rank[y]) swap(x, y);

        p[x] = y;

        if (m_child) {
            for (auto &e : childs[x]) {
                childs[y].push_back(e);
            }

            childs[x].clear();
        }

        maxIn[y] = max(maxIn[x], maxIn[y]);
        minIn[y] = min(minIn[x], minIn[y]);

        if (rank[x] == rank[y]) rank[y]++;

        setSize[y] += setSize[x];
        --numSets;
    }
};

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

    int query(int r) {
        return sum(r);
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

bool input(int &n, int &k, vector<tuple<int, int, int>> &queries) {
    cin >> n >> k;
    queries.clear();

    bool isSub2 = true;

    for (int i=0, u, v, f; i<k; i++) {
        string str; cin >> str;
        if (str[0] == 'j') {
            f = 1;
            cin >> u >> v;
            if (abs(u - v) > 1) isSub2 = false;
        } else if (str[0] == 'a') {
            f = 2;
            cin >> u >> v;
        } else if (str[0] == 'g') {
            f = 3;
            cin >> u;
            v = -1;
        }

        queries.push_back({f, u, v});
    }

    return isSub2;
}

void sub_1(int n, int k, const vector<tuple<int, int, int>> &queries) {
    DSU dsu(n + 1, true);

    for (int i=0; i<k; i++) {
        auto [f, u, v] = queries[i];

        if (f == 1) {
            dsu.unionSet(u, v);
        } else if (f == 2) {
            dsu.addValue(u, v);
        } else if (f == 3) {
            cout << dsu.getValue(u) << "\n";
        }
    }
}

void sub_2(int n, int k, const vector<tuple<int, int, int>> &queries) {
    DSU dsu(n + 1, false);
    FenwickTree ft(n + 5);

    for (int i=0; i<k; i++) {
        auto [f, u, v] = queries[i];

        if (f == 1) {
            dsu.unionSet(u, v);
        } else if (f == 2) {
            int l = dsu.getMin(u);
            int r = dsu.getMax(u);

            ft.add(l, v);
            ft.add(r + 1, -v);
        } else if (f == 3) {
            cout << ft.query(u) << "\n";
        }
    }
}

void sub_3(int n, int k, const vector<tuple<int, int, int>> &queries) {

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k;
    vector<tuple<int, int, int>> queries;
    bool isSub2 = input(n, k, queries);

    if (n <= 5000 & k <= 5000) sub_1(n, k, queries);
    else if (isSub2) sub_2(n, k, queries);
    else sub_3(n, k, queries);

    return 0;
}