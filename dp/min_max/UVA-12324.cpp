// https://vjudge.net/problem/UVA-12324

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n;
    while (cin >> n) {
        if (!n) break;

        vector<pair<int, int>> trip(n+1);
        for (int i=1; i<=n; i++) cin >> trip[i].first >> trip[i].second;

        for (int i=1; i<=n; i++) {
            for (int j=i+1; j<=n; j++) {
                
            }
        }
    }

    return 0;
}