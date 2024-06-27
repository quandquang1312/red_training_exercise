// // https://vjudge.net/problem/UVA-459

#include <bits/stdc++.h>
using namespace std;

vector<int> par, sz;

void make_set(int v) {
    par[v] = v;
    sz[v] = 1;
}

int find_set(int v) {
    if (v == par[v]) return v;
    return par[v] = find_set(par[v]);
}

void union_sets(int a, int b) {
    int par_a = find_set(a);
    int par_b = find_set(b);

    if (par_a != par_b) {
        if (sz[par_a] < sz[par_b])
            swap(par_a, par_b);
        
        par[par_b] = par_a;
        sz[par_a] += sz[par_b];
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    string first_line;
    while (tc--) {
        char l; cin >> l;
        cin.ignore();

        int n = 30, a, b;

        par.clear();
        sz.clear();
        par.resize(n+1);
        sz.resize(n+1);

        for (int i=1; i<=n; i++)
            make_set(i);

        string line;
        while (getline(cin, line) && line != "")
        {
            char tmp_a, tmp_b;
            tmp_a = line[0], tmp_b = line[1];
            a = tmp_a - 64;
            b = tmp_b - 64;

            // cout << a << "-" << b << endl;

            union_sets(a, b);
        }

        set<int> set_par;
        for (int i=1; i<=l-64; i++) {
            int parent_i = find_set(i);
            set_par.insert(parent_i);
        }

        cout << set_par.size() << endl;
        if (tc) cout << endl;
    }

    return 0;
}