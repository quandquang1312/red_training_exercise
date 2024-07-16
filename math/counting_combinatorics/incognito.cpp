// https://open.kattis.com/problems/incognito?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--)
    {
        int n; cin >> n;

        string a, b;
        map<string, int> cate;
        for (int i=0; i<n; i++) {
            cin >> a >> b;
            cate[b]++;
        }

        int ans = 1;
        for (auto &[i, c] : cate) {
            ans *= (c+1);
        }

        cout << ans - 1 << endl;
    }

    return 0;
}