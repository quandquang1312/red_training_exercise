// https://codejam.lge.com/problem/28312

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

bool check(int val, int no_interval, vector<int>& arr) {
    int interval_used = 1;
    int rm = 0, sm = 0, cnt = 1;
    // count the sum of every sebsequence in an array
    for (int i=0; i<arr.size(); i++) {
        if (interval_used > no_interval) return false;
        rm += arr[i] * cnt;
        if (sm + rm <= val) {
            sm += rm;
            cnt++;
        } else {
            rm = 0, sm = 0, cnt = 1;
            interval_used++;
        }
    }

    return interval_used <= no_interval;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<int> arr(n-1);
        for (int i=0; i<n-1; i++) cin >> arr[i];

        int l = 0, r = INF - 1;

        // for (int i=0; i<20; i++) {
        //     cout << i << ": " << check(i, m, arr) << "\n";
        // }

        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid, m, arr)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        cout << l << "\n";
    }

    return 0;
}