// https://vjudge.net/problem/UVA-12036

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

    int tc, t = 1; cin >> tc;
    while (tc--)
    {
        int n; cin >> n;
        unordered_map<int, int> mp;

        for (int i=0; i<n*n; i++) {
            int cell; cin >> cell;
            mp[cell]++;
        }

        string ans = "yes";
        for (auto &[k, v] : mp) {
            if (v > n) {
                ans = "no";
                break;
            }
        }

        cout << "Case " << t++ << ": " << ans << endl;
    }

    return 0;
}