// https://vjudge.net/problem/UVA-10223
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

    vector<int> cat(22, 0);
    cat[0] = 1;
    for (int i=0; i<21; i++) {
        cat[i+1] = ((4*i + 2) * cat[i]) / (i + 2);
        // cout << i << ": " << cat[i] << endl;
    }

    int n;
    while (cin >> n) {
        int ans = 0;
        for (int i=0; i<cat.size(); i++) {
            if (cat[i] == n) {
                ans = i;
                break;
            }
        }

        cout << ans << endl;
    }

    return 0;
}