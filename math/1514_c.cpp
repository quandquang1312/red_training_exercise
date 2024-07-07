// https://codeforces.com/problemset/problem/1514/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, p = 1; cin >> n;

    set<int> st;
    for (int i=1; i<=n; i++) {
        if (__gcd(i, n) == 1) {
            st.insert(i);
            p = (p * i) % n;
        }
    }

    if (p % n != 1)
        st.erase(p%n);

    cout << st.size() << endl;
    for (auto &e : st) {
        cout << e << " ";
    } cout << endl;

    return 0;
}