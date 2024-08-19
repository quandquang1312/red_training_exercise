// https://usaco.org/index.php?page=viewproblem2&cpid=1085

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

    int n; cin >> n;
    vector<int> cows(n), stail(n);

    for (int i=0; i<n; i++) cin >> cows[i];
    for (int i=0; i<n; i++) cin >> stail[i];

    sort(cows.rbegin(), cows.rend());
    sort(stail.begin(), stail.end());

    int lst = n, ans = 1;
    for (int i=0; i<n; i++) {
        int pos = lower_bound(stail.begin(), stail.end(), cows[i]) - stail.begin();
        if (pos == n) {
            ans = 0;
            break;
        }

        ans *= (lst - pos);
        lst -= 1;
    }

    cout << ans << endl;

    return 0;
}