// https://atcoder.jp/contests/abc319/tasks/abc319_d

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

    int n, m; cin >> n >> m;
    vector<int> L(n);

    int mmax = 0;
    for (int i=0; i<n; i++) {
        cin >> L[i];
        mmax = max(mmax, L[i]);
    }

    auto F = [&] (int x) -> int {
        int line = 1, curWidth = 0;
        for (int i=0; i<n; i++) {
            if (L[i] > x) return -1;
            if (curWidth + L[i] <= x) curWidth += (L[i] + 1);
            else {
                line++;
                curWidth = L[i] + 1; 
            }
        }

        return line;
    };

    for (int i=mmax; i<=30; i++) {
        cout << i << ": " << F(i) << "\n";
    }

    // int l=0, r=1e18;
    // while (l < r) {
    //     int x = (l + r) / 2;
    //     if (F(x)) r = x;
    //     else l = x + 1; 
    // }

    // cout << l << "\n";

    return 0;
}