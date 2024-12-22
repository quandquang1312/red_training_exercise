// https://codeforces.com/problemset/problem/1791/D

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
    while (tc--) {
        int n; cin >> n;
        string str; cin >> str;

        int cnt[26] {}, cnt2[26] {};
        for (int i=0; i<n; i++) {
            cnt2[str[i] - 'a']++;
        }

        int ans = 0;
        for (int i=0; i<n; i++) {
            cnt2[str[i] - 'a']--;
            cnt[str[i] - 'a']++;

            int c1 = 0, c2 = 0;
            for (int i=0; i<26; i++) {
                if (cnt[i]) c1++;
                if (cnt2[i]) c2++;
            }

            ans = max(ans, c1 + c2);
        }

        cout << ans << "\n";
    }

    return 0;
}