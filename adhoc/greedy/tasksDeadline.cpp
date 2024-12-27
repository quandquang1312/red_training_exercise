// https://vjudge.net/problem/CSES-1630

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
    vector<pair<int, int>> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i].first >> arr[i].second;
 
    sort(arr.begin(), arr.end());

    int max_ans = 0, cur = 0;
    for (int i=0; i<n; i++) {
        cur += arr[i].first;
        max_ans += (arr[i].second - cur);
    }

    cout << max_ans << "\n";

    return 0;
}