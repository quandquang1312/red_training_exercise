// https://codejam.lge.com/problem/18768

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
        int n, k; cin >> n >> k;
        vector<pair<int, int>> arr(n);

        for (int i=0; i<n; i++) cin >> arr[i].first;
        for (int i=0; i<n; i++) cin >> arr[i].second;

        // calculate the least number of member each team must have
        int ans = 0;
        int choose_each = (n - k + 1) / 2;

        // sort base the difference of A skill - B skill (cause we pick A first) 
        sort(arr.begin(), arr.end(), [](pair<int, int> p1, pair<int, int> p2) {
            int max_diff1 = p1.first - p1.second;
            int max_diff2 = p2.first - p2.second;
            return max_diff1 > max_diff2;
        });

        // Pick the least number of A (from 0) cause we sort in difference of flavour A
        // Pick the least number of B (from last)
        // The reamin is free, we can pick whatever maximum the score for us

        for (int i=0; i<choose_each; i++) ans += arr[i].first;
        for (int i=n-1; i>=n-choose_each; i--) ans+= arr[i].second;
        for (int i=choose_each; i<n-choose_each; i++) ans += max(arr[i].first, arr[i].second);

        cout << ans << endl;
    }

    return 0;
}