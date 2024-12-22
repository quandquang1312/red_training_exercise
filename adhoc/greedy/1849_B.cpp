// https://codeforces.com/contest/1849/problem/B

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
        for (int i=0; i<n; i++) {
            cin >> arr[i].first;
            arr[i].second = i;
        }

        for (int i=0; i<n; i++) {
            arr[i].first %= k;
            if (arr[i].first == 0) arr[i].first = k;
        }

        sort(arr.begin(), arr.end(), [] (pair<int, int> &p1, pair<int, int> &p2) {
            if (p1.first == p2.first) return p1.second < p2.second;
            return p1.first > p2.first;
        });

        for (int i=0; i<n; i++) cout << arr[i].second + 1 << " ";
        cout << "\n";
    }

    return 0;
}