#include <bits/stdc++.h>
using namespace std;

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

        vector<char> vowel = {'a', 'e', 'i', 'o', 'u'};
        if (n <= vowel.size()) {
            string ans;
            for (int i=0; i<n; i++) ans.push_back(vowel[i]);
            cout << ans << endl;
        } else {
            string ans;
            int part = n / vowel.size();
            vector<int> cnt(vowel.size(), part);
            int rm = n % vowel.size();
            for (int i=0; i<rm; i++) cnt[i] += 1;
            
            for (int v=0; v<vowel.size(); v++) {
                for (int i=0; i<cnt[v]; i++) {
                    ans.push_back(vowel[v]);
                }
            }

            cout << ans << '\n';
        }
    }

    return 0;
}