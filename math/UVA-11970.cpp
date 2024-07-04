// https://vjudge.net/problem/UVA-11970

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
    while (tc--) {
        int n; cin >> n;

        vector<int> ans;
        for (int i=1; i*i < n; i++) {
            int x = n - (i*i);
            if (x % i == 0) ans.push_back(x);
        }

        sort(ans.begin(), ans.end());
        cout << "Case " << t++ << ":";
        for (int i=0; i<ans.size(); i++)
            cout << " " << ans[i]; // << " ";
        cout << endl;
    }

    return 0;
}